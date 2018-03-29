set nocompatible
filetype off

"Plugins 
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

"Syntax
Plugin 'jelera/vim-javascript-syntax'
Plugin 'plasticboy/vim-markdown'
Plugin 'slim-template/vim-slim'
Plugin 'hail2u/vim-css3-syntax'
Plugin 'tikhomirov/vim-glsl'
Plugin 'keith/swift.vim'
Plugin 'lervag/vimtex'

"Themes
Plugin 'nanotech/jellybeans.vim'
Plugin 'dikiaap/minimalist'
Plugin 'morhetz/gruvbox'
Plugin 'w0ng/vim-hybrid'

"Misc
Plugin 'VundleVim/Vundle.vim'
Plugin 'scrooloose/nerdtree'
Plugin 'vim-syntastic/syntastic'
Plugin 'valloric/YouCompleteMe'
Plugin 'alvan/vim-closetag'
Plugin 'gko/vim-coloresque'
Plugin 'jeaye/color_coded'
Plugin 'junegunn/goyo.vim'
Plugin 'vim-scripts/Conque-GDB'
Plugin 'xolox/vim-misc'
Plugin 'xolox/vim-easytags'
Plugin 'majutsushi/tagbar'

call vundle#end()
filetype plugin on

"Plugin settings 
let g:jellybeans_use_term_italics = 1
let g:gruvbox_italic = 1
let g:gruvbox_contrast_dark = "hard"
let c_no_curly_error = 1
let g:vim_markdown_folding_disabled = 1

let g:NERDTreeWinSize = 25
let g:ycm_confirm_extra_conf = 0
let g:ycm_register_as_syntastic_checker = 1
let g:ConqueTerm_Color = 2
let g:ConqueTerm_CloseOnEnd = 1
let g:ConqueTerm_StartMessages = 0
let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_c_compiler_options = '-std=c11 -fplan9-extensions'
let g:goyo_height = 200

"Settings
set encoding=utf-8
set fileencoding=utf-8
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*
set background=dark
set hlsearch
set textwidth=80
set cc=81
set tabstop=4
set shiftwidth=4
set wildmenu
set autoindent
set mouse=
set omnifunc=syntaxcomplete#Complete
set history=10000
set undolevels=10000
set undofile
set undodir=~/.vim/undo
set laststatus=0
set t_Co=256
set autochdir
set fo+=t
set fo-=l

"Key bindings
inoremap <C-c> <Esc>
inoremap " ""<left>
inoremap ' ''<left>
inoremap [ []<left>
inoremap ( ()<left>
inoremap { {}<left>
inoremap {<cr> {<cr>}<C-c>O<tab>

noremap ; :
noremap j gj
noremap k gk
noremap <C-c> <Esc>
noremap <leader>~ :TagbarToggle<CR>
noremap <F5> :ConqueGdbVSplit a.out<enter>
noremap <leader><Tab> :cd %:p:h<CR>:NERDTreeToggle<CR>

vnoremap <C-c> <Esc>

"Theme settings
syntax on
color gruvbox
highlight Normal ctermbg=none guibg=black
highlight NonText ctermbg=none guibg=black
highlight Member ctermfg=White guifg=White
highlight Variable ctermfg=White guifg=White

"Syntax filetype settings
autocmd BufNewFile,BufRead *.nasm set syntax=nasm
autocmd BufNewFile,BufRead *.yapl set syntax=yapl
autocmd BufNewFile,BufRead *.erw set syntax=erw
autocmd BufNewFile,BufRead *.slim setlocal filetype=slim

