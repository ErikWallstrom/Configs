set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
Plugin 'scrooloose/nerdtree'
Plugin 'jiangmiao/auto-pairs'
Plugin 'vim-scripts/brainfuck-syntax'
Plugin 'nanotech/jellybeans.vim'
Plugin 'valloric/YouCompleteMe'
Plugin 'rust-lang/rust.vim'

call vundle#end()
filetype plugin indent on

"Airline settings
set laststatus=2
set ttimeoutlen=50
let g:airline_theme = 'simple'
let g:airline_powerline_fonts = 1

"Nerdtree settings
noremap <Tab> :NERDTreeToggle<CR>
let g:NERDTreeWinSize = 20

"Auto-pairs settings
let g:AutoPairsShortcutFastWrap='<Nop>' "Fix å

"Ycm settings
let g:ycm_confirm_extra_conf = 0

set t_Co=256
syntax on
"C syntax highlighting
let c_hi_identifiers = 'all'
let c_hi_libs = ['*']  

set tabstop=4
set shiftwidth=4
set noexpandtab
"set number
set wildmenu
set autoindent
set wrap
set linebreak
set mouse= 
set backspace=2

set history=10000
set undolevels=10000
set undofile
set undodir=/home/erikwallstrom/.vim/undo
set backupdir=/home/erikwallstrom/.vim/backup
set directory=/home/erikwallstrom/.vim/swap

highlight ColorColumn ctermbg=red
call matchadd('ColorColumn', '\%81v', 100)

inoremap <C-c> <Esc>
inoremap <Esc> <C-c>
noremap ; :
noremap j gj

noremap k gk
color jellybeans
