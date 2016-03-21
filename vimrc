"Initialize vim
set nocompatible
filetype off

"PLUGINS
"==================================================
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'jiangmiao/auto-pairs'
Plugin 'Valloric/YouCompleteMe'
Plugin 'xolox/vim-misc'
Plugin 'xolox/vim-easytags'
Plugin 'scrooloose/nerdtree'
Plugin 'nathanaelkane/vim-indent-guides'
Plugin 'tikhomirov/vim-glsl'

call vundle#end()
filetype plugin indent on

"Airline settings
set laststatus=2
set ttimeoutlen=50
let g:airline_theme = 'simple'
let g:airline_powerline_fonts = 1

"Auto-pairs settings
let g:AutoPairsShortcutFastWrap='<Nop>' "Fix å

"YouCompleteMe settings
let g:ycm_confirm_extra_conf = 0
let g:ycm_min_num_of_chars_for_completion = 99
let g:ycm_autoclose_preview_window_after_insertion = 1

"Vim-easytags settings
let g:easytags_always_enabled = 1

"NerdTREE settings
nmap <Tab> :NERDTreeToggle<CR>
let g:NERDTreeWinSize = 22

"Indent_Guides settings
set ts=4 sw=4 et
let g:indent_guides_guide_size = 1
"==================================================

"Syntax coloring
set t_Co=256
syntax on
set background=dark
color koehler

"Tab width
set tabstop=4
set shiftwidth=4

"Line numbering
set number

"Tab completion in commands
set wildmenu

"Map Ctrl-c to work as Esc
inoremap <C-c> <Esc>
inoremap <Esc> <C-c>

"Map semicolon to colon
noremap ; :
noremap : :

"Show matching parenthesis
set showmatch

"Indentation settings
set backspace=indent,eol,start
set autoindent
set noexpandtab

"Random setting
set history=10000
set undolevels=10000
set hidden
set undofile
set undodir=/home/erikwallstrom/.vim/undo//
set backupdir=/home/erikwallstrom/.vim/backup//
set directory=/home/erikwallstrom/.vim/swap//
set wrap
set linebreak
set mouse=

"GUI settings
set guioptions-=T "Remove toolbar
set guioptions-=r "Remove scrollbar
set guioptions-=L "Remove scrollbar
set guioptions-=m "Remove menu
set guifont=Cousine\ for\ Powerline\ 18
set guiheadroom=0
set guioptions-=e

map j gj
map k gk
