#include <gtk/gtk.h>

void list_row_clicked(GtkListBox* list, GtkListBoxRow* row, gpointer user_data)
{
	GtkWidget* stack = gtk_widget_get_parent(GTK_WIDGET(list));
	gtk_stack_set_visible_child_name(
		GTK_STACK(stack), 
		gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row))))
	);
	gtk_widget_show_all(stack);
}

void activate(GtkApplication* app, gpointer user_data)
{
	GtkWidget* window = gtk_application_window_new(app);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	GtkWidget* header = gtk_header_bar_new();
	gtk_header_bar_set_title(GTK_HEADER_BAR(header), "Choose a project");
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header), TRUE);
	gtk_header_bar_set_has_subtitle(GTK_HEADER_BAR(header), FALSE);
	gtk_window_set_titlebar(GTK_WINDOW(window), header);

	GtkWidget* stack = gtk_stack_new();
	GtkWidget* list = gtk_list_box_new();
	GtkWidget* test = gtk_stack_new();

	GDir* dir = g_dir_open(".", 0, NULL);
	for(const char* name = NULL; name = g_dir_read_name(dir);)
	{
		if(g_file_test(name, G_FILE_TEST_IS_DIR))
		{
			GString* test_dir_name = g_string_new(name);
			g_string_append(test_dir_name, "/test");
			if(g_file_test(test_dir_name->str, G_FILE_TEST_IS_DIR))
			{
				GtkWidget* label = gtk_label_new(name);
				gtk_container_add(GTK_CONTAINER(list), label);

				GtkWidget* tests = gtk_stack_new();
				GtkWidget* side_bar = gtk_stack_sidebar_new();
				gtk_stack_sidebar_set_stack(
					GTK_STACK_SIDEBAR(side_bar),
					GTK_STACK(tests)
				);
				GtkWidget* pane = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
				gtk_paned_add1(GTK_PANED(pane), side_bar);
				gtk_paned_add2(GTK_PANED(pane), tests);

				GDir* dir = g_dir_open(test_dir_name->str, 0, NULL);
				for(const char* test = NULL; test = g_dir_read_name(dir);)
				{
					g_print("%s\n", test);
					if(g_ascii_strncasecmp(test, "test", 4))
					{
						GtkWidget* text = gtk_label_new(test);
						gtk_stack_add_titled(GTK_STACK(tests), text, test, test);
						gtk_widget_show_all(tests);
					}
				}
				g_dir_close(dir);
				gtk_stack_add_named(GTK_STACK(stack), pane, name);
				gtk_widget_show_all(GTK_WIDGET(pane));
			}

			g_string_free(test_dir_name, TRUE);
		}
	}
	g_dir_close(dir);
	g_signal_connect(list, "row-activated", G_CALLBACK(list_row_clicked), NULL);

	if(g_list_length(gtk_container_get_children(GTK_CONTAINER(list))))
	{
		gtk_stack_add_named(GTK_STACK(stack), list, "list");
		gtk_widget_show_all(GTK_WIDGET(stack));
	}
	else
	{
		GtkWidget* no_project = gtk_label_new("No projects were found");
		gtk_stack_add_named(GTK_STACK(stack), no_project, "list");
	}
	
	gtk_stack_set_visible_child_name(GTK_STACK(stack), "list");
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

