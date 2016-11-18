#include <gtk/gtk.h>
#include <vte/vte.h>
#include <string.h>

void on_back_clicked(GtkButton* button, gpointer user_data)
{
	GtkStack* stack = GTK_STACK(user_data);
	gtk_stack_set_transition_type(
		stack, 
		GTK_STACK_TRANSITION_TYPE_SLIDE_RIGHT
	);
	gtk_stack_set_visible_child_name(stack, "list");
	gtk_stack_set_transition_type(
		stack, 
		GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT
	);
	gtk_container_remove(
		GTK_CONTAINER(
			gtk_window_get_titlebar(
				GTK_WINDOW(gtk_widget_get_parent(GTK_WIDGET(stack)))
			)
		),
		GTK_WIDGET(button)
	);
}

void on_list_click(GtkListBox* box, GtkListBoxRow* row, gpointer user_data)
{
	gtk_widget_show_all(gtk_stack_get_visible_child(
		GTK_STACK(gtk_widget_get_parent(GTK_WIDGET(box))))
	);
	gtk_stack_set_visible_child_name(
		GTK_STACK(gtk_widget_get_parent(GTK_WIDGET(box))),
		gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row))))
	);

	GtkHeaderBar* header = GTK_HEADER_BAR(user_data);
	GtkWidget* back_button = gtk_button_new_with_label("Back");
	g_signal_connect(
		back_button,
		"clicked", 
		G_CALLBACK(on_back_clicked),
		GTK_STACK(gtk_widget_get_parent(GTK_WIDGET(box)))
	);
	gtk_container_add(GTK_CONTAINER(header), back_button);
	GtkWidget* refresh_button = gtk_button_new_from_icon_name(
		"gtk-refresh", 
		GTK_ICON_SIZE_MENU
	);
	gtk_header_bar_pack_end(GTK_HEADER_BAR(header), refresh_button);
	gtk_widget_show_all(GTK_WIDGET(header));
}

gint find_string(gconstpointer item, gconstpointer str)
{
	return g_ascii_strcasecmp(
		gtk_label_get_text(
			GTK_LABEL(gtk_bin_get_child(GTK_BIN(item)))
		), 
		str
	);
}

void on_list_refresh(GtkButton* button, gpointer user_data)
{
	GtkStack* stack = GTK_STACK(user_data);
	GtkWidget* list = gtk_stack_get_visible_child(stack);
	GList* list_items = gtk_container_get_children(GTK_CONTAINER(list));
	
	GDir* dir = g_dir_open(".", 0, NULL);
	for(const char* name = NULL; name = g_dir_read_name(dir);)
	{
		if(g_file_test(name, G_FILE_TEST_IS_DIR))
		{
			if(!g_list_find_custom(list_items, name, find_string))
			{
				GtkWidget* label = gtk_label_new(name);
				gtk_container_add(GTK_CONTAINER(list), label);
			}
		}
	}
	g_dir_close(dir);
	gtk_widget_show_all(list);
}

void on_project_refresh(GtkButton* button, gpointer user_data)
{

}

GtkWidget* create_window(GtkApplication* app)
{
	GtkWidget* window = gtk_application_window_new(app);
	gtk_window_set_default_size(GTK_WINDOW(window), 850, 525);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	GtkWidget* header = gtk_header_bar_new();
	gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Project Tester");
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
	gtk_header_bar_set_has_subtitle(GTK_HEADER_BAR(header), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(window), header);
	
	GtkWidget* stack = gtk_stack_new();
	GtkWidget* empty = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_container_add(GTK_CONTAINER(empty), gtk_label_new(""));
	GtkWidget* back_button = gtk_button_new_with_label("Back");
	g_signal_connect(
		back_button,
		"clicked", 
		G_CALLBACK(on_back_clicked),
		stack
	);
	gtk_stack_add_named(GTK_STACK(stack), empty, "empty");
	gtk_stack_add_named(GTK_STACK(stack), back_button, "back");
	gtk_header_bar_pack_start(GTK_HEADER_BAR(header), stack);
	gtk_widget_show_all(GTK_WIDGET(header));
	gtk_stack_set_visible_child(GTK_STACK(stack), empty);

	GtkWidget* refresh_button = gtk_button_new_from_icon_name(
		"gtk-refresh", 
		GTK_ICON_SIZE_MENU
	);
	gtk_header_bar_pack_end(GTK_HEADER_BAR(header), refresh_button);

	return window;
}

GtkWidget* create_list(void)
{
	GtkWidget* list = gtk_list_box_new();
	GDir* dir = g_dir_open(".", 0, NULL);
	for(const char* name = NULL; name = g_dir_read_name(dir);)
	{
		if(g_file_test(name, G_FILE_TEST_IS_DIR))
		{
			GtkWidget* label = gtk_label_new(name);
			gtk_container_add(GTK_CONTAINER(list), label);
		}
	}
	g_dir_close(dir);
	return list;
}

GtkWidget* create_project(const char* project)
{
	GtkWidget* paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_set_wide_handle(GTK_PANED(paned), TRUE);
	GtkWidget* stack = gtk_stack_new();
	GtkWidget* sidebar = gtk_stack_sidebar_new();

	GString* string = g_string_new(project);
	g_string_append(string, "/test");
	if(g_file_test(string->str, G_FILE_TEST_IS_DIR))
	{
		GDir* dir = g_dir_open(string->str, 0, NULL);
		for(const char* name; name = g_dir_read_name(dir);)
		{
			if(!g_ascii_strncasecmp(name, "test", 4))
			{
				GString* script = g_string_new("ruby ");
				g_string_append(script, string->str);
				g_string_append(script, "/");
				g_string_append(script, name);

				char* result;
				g_spawn_command_line_sync(
					script->str,
					&result,
					NULL,
					NULL,
					NULL
				);

				GtkWidget* vte = vte_terminal_new();
				vte_terminal_set_rewrap_on_resize(
					VTE_TERMINAL(vte),
					TRUE
				);
				for(int i = 0; i < strlen(result); i++)
				{
					if(result[i] == '\n')
					{
						vte_terminal_feed(
							VTE_TERMINAL(vte), 
							"\r\n",
							2
						);
					}
					else
						vte_terminal_feed(
							VTE_TERMINAL(vte), 
							result + i,
							1
						);
				}

				GtkWidget* inner_box = gtk_box_new(
					GTK_ORIENTATION_HORIZONTAL, 0
				);
				gtk_box_pack_start(
					GTK_BOX(inner_box), 
					vte,
					TRUE,
					TRUE,
					0
				);

				gtk_stack_add_titled(
					GTK_STACK(stack), 
					inner_box, name, name
				);
				g_string_free(script, TRUE);
			}
		}
	}
	g_string_free(string, TRUE);

	gtk_paned_add1(GTK_PANED(paned), sidebar);
	gtk_paned_add2(GTK_PANED(paned), stack);
	gtk_stack_sidebar_set_stack(
		GTK_STACK_SIDEBAR(sidebar), 
		GTK_STACK(stack)
	);

	return paned;
}

void activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget* window = create_window(app);
	GtkWidget* stack = gtk_stack_new();
	gtk_stack_set_transition_type(
		GTK_STACK(stack), 
		GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT
	);
	gtk_stack_set_transition_duration(GTK_STACK(stack), 500);

	g_signal_connect(
		gtk_window_get_titlebar(GTK_WINDOW(window)),
		"clicked", 
		G_CALLBACK(on_list_refresh),
		stack
	);

	GtkWidget* list = create_list();
	g_signal_connect(
		list, 
		"row-activated", 
		G_CALLBACK(on_list_click),
		gtk_window_get_titlebar(GTK_WINDOW(window))
	);
	gtk_stack_add_named(GTK_STACK(stack), list, "list");
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "list");

	for(GList* l = gtk_container_get_children(GTK_CONTAINER(list)); 
		l != NULL; l = l->next
	)
	{
		GtkWidget* paned = create_project(
			gtk_label_get_text(
				GTK_LABEL(gtk_bin_get_child(GTK_BIN(l->data)))
			)
		);
		gtk_stack_add_named(
			GTK_STACK(stack), 
			paned, 
			gtk_label_get_text(
				GTK_LABEL(gtk_bin_get_child(GTK_BIN(l->data)))
			)
		);
	}

	gtk_container_add(GTK_CONTAINER(window), stack);
	gtk_widget_show_all(window);
}

int main(int argc, char* argv[])
{
	GtkApplication* app = gtk_application_new(
		"com.github.ErikWallstrom.Project_Tester",
		G_APPLICATION_FLAGS_NONE
	);

	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	int status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}

