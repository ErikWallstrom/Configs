"Initialize vim
set nocompatible
filetype off

"PLUGINS
"==================================================
"Vundle
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
Plugin 'bbchung/clighter'

call vundle#end()
filetype plugin indent on

"Airline settings
set laststatus=2
set ttimeoutlen=50
let g:airline_theme = 'simple'
let g:airline_powerline_fonts = 1

"YouCompleteMe settings
let g:ycm_confirm_extra_conf = 0
let g:ycm_min_num_of_chars_for_completion = 99
autocmd InsertLeave * if pumvisible() == 0|pclose|endif

"Vim-easytags settings
let g:easytags_always_enabled = 1

"Easytags settings
let g:easytags_always_enabled = 1

"NerdTREE settings
nmap <Tab> :NERDTreeToggle<CR>

"Clighter settings
let g:clighter_libclang_file = '/usr/lib/llvm-3.6/lib/libclang-3.6.so'
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
noremap <C-c> <Esc>

"Map semicolon to colon
noremap ; :
noremap : :

"Disable mouse
set mouse=
set mouse=""

"Show matching parenthesis
set showmatch

"Indentation settings
set backspace=indent,eol,start
set autoindent

"Random setting
set history=1000
set undolevels=1000
set nobackup
set noswapfile
set wrap
set linebreak

map j gj
map k gk
