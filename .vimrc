set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
"Plugin 'vim-airline/vim-airline'
"Plugin 'vim-airline/vim-airline-themes'
Plugin 'scrooloose/nerdtree'
Plugin 'jiangmiao/auto-pairs'
Plugin 'vim-scripts/brainfuck-syntax'
Plugin 'nanotech/jellybeans.vim'
Plugin 'valloric/YouCompleteMe'
Plugin 'rust-lang/rust.vim'
Plugin 'xolox/vim-misc'
Plugin 'xolox/vim-easytags'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'tpope/vim-rails'
Plugin 'scrooloose/syntastic'
Plugin 'alvan/vim-closetag'
Plugin 'othree/html5.vim'
Plugin 'godlygeek/tabular'
Plugin 'plasticboy/vim-markdown'
Plugin 'hail2u/vim-css3-syntax'
Plugin 'gko/vim-coloresque'
Plugin 'chriskempson/base16-vim'
Plugin 'neovimhaskell/haskell-vim'
Plugin 'romainl/Apprentice'

call vundle#end()
filetype plugin indent on

"Airline settings
set laststatus=0
set ttimeoutlen=50
let g:airline_theme = 'simple'
let g:airline_powerline_fonts = 1

"Nerdtree settings
noremap <Tab> :cd %:p:h<CR>:NERDTreeToggle<CR>
let g:NERDTreeWinSize = 20

"Auto-pairs settings
let g:AutoPairsShortcutFastWrap='<Nop>' "Fix å

"Ycm settings
let g:ycm_confirm_extra_conf = 0
"let g:ycm_autoclose_preview_window_after_insertion = 1

"Easytags settings
let g:easytags_include_members = 1

"UltiSnips settings
let g:UltiSnipsExpandTrigger="<enter>"
let g:UltiSnipsJumpForwardTrigger="<c-a>"

"Syntastic settings
let g:syntastic_asm_checkers=['']

"Base16 settings
let base16colorspace=256

"Haskell settings
let g:haskell_enable_quantification = 1   " to enable highlighting of `forall`
let g:haskell_enable_recursivedo = 1      " to enable highlighting of `mdo` and `rec`
let g:haskell_enable_arrowsyntax = 1      " to enable highlighting of `proc`
let g:haskell_enable_pattern_synonyms = 1 " to enable highlighting of `pattern`
let g:haskell_enable_typeroles = 1        " to enable highlighting of type roles
let g:haskell_enable_static_pointers = 1  " to enable highlighting of `static`

let c_no_curly_error = 1
set t_Co=256
syntax on

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
set omnifunc=syntaxcomplete#Complete

set history=10000
set undolevels=10000
set undofile
set undodir=/home/erikwallstrom/.vim/undo

noremap ; :
noremap j gj
noremap k gk

color jellybeans

highlight ColorColumn ctermbg=red guibg=#FF0000
autocmd BufNewFile,BufRead *.asm set syntax=nasm

