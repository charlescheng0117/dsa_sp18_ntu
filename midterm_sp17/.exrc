if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <Plug>(neocomplete_auto_refresh) =neocomplete#mappings#refresh()
inoremap <silent> <Plug>(neocomplete_start_manual_complete) =neocomplete#mappings#manual_complete()
inoremap <silent> <Plug>(neocomplete_start_auto_complete) =neocomplete#mappings#auto_complete()
inoremap <silent> <Plug>(neocomplete_start_omni_complete) 
inoremap <silent> <expr> <Plug>(neocomplete_start_unite_quick_match) unite#sources#neocomplete#start_quick_match()
inoremap <silent> <expr> <Plug>(neocomplete_start_unite_complete) unite#sources#neocomplete#start_complete()
inoremap <silent> <expr> <Plug>delimitMateS-BS delimitMate#WithinEmptyPair() ? "\<Del>" : "\<S-BS>"
inoremap <silent> <Plug>delimitMateBS =delimitMate#BS()
inoremap <silent> <C-Tab> =UltiSnips#ListSnippets()
inoremap <expr> <BS> neocomplete#smart_close_popup()."\"
map! <D-v> *
snoremap <silent>  c
xnoremap <silent> 	 :call UltiSnips#SaveLastVisualSelection()gvs
snoremap <silent> 	 :call UltiSnips#ExpandSnippetOrJump()
snoremap  "_c
nmap \j <Plug>(CommandTJump)
nmap \b <Plug>(CommandTBuffer)
nmap \t <Plug>(CommandT)
xmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
nnoremap <silent> <Plug>(CommandTTag) :CommandTTag
nnoremap <silent> <Plug>(CommandTSearch) :CommandTSearch
nnoremap <silent> <Plug>(CommandTMRU) :CommandTMRU
nnoremap <silent> <Plug>(CommandTLine) :CommandTLine
nnoremap <silent> <Plug>(CommandTCommand) :CommandTCommand
nnoremap <silent> <Plug>(CommandTJump) :CommandTJump
nnoremap <silent> <Plug>(CommandTHistory) :CommandTHistory
nnoremap <silent> <Plug>(CommandTHelp) :CommandTHelp
nnoremap <silent> <Plug>(CommandTBuffer) :CommandTBuffer
nnoremap <silent> <Plug>(CommandT) :CommandT
nnoremap <SNR>23_: :=v:count ? v:count : ''
snoremap <silent> <Del> c
snoremap <silent> <BS> c
snoremap <silent> <C-Tab> :call UltiSnips#ListSnippets()
xmap <BS> "-d
vmap <D-x> "*d
vmap <D-c> "*y
vmap <D-v> "-d"*P
nmap <D-v> "*P
inoremap <expr>  neocomplete#undo_completion()
inoremap <expr>  neocomplete#smart_close_popup()."\"
inoremap <silent> 	 =g:UltiSnips_Complete()
inoremap <expr>  neocomplete#complete_common_string()
let &cpo=s:cpo_save
unlet s:cpo_save
set backspace=2
set completeopt=preview,menuone
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set runtimepath=~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/neocomplete.vim,~/.vim/bundle/ultisnips,~/.vim/bundle/VimCompleteLikeAModernEditor,~/.vim/bundle/AutoComplPop,~/.vim/bundle/vim-snippets,~/.vim/bundle/delimitmate,~/.vim/bundle/vim-fugitive,~/.vim/bundle/command-t,~/.vim/bundle/plugin,~/.vim/bundle/sparkup/vim/,/usr/local/share/vim/vimfiles,/usr/local/share/vim/vim80,/usr/local/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/Vundle.vim,~/.vim/bundle/Vundle.vim/after,~/.vim/bundle/neocomplete.vim/after,~/.vim/bundle/ultisnips/after,~/.vim/bundle/VimCompleteLikeAModernEditor/after,~/.vim/bundle/AutoComplPop/after,~/.vim/bundle/vim-snippets/after,~/.vim/bundle/delimitmate/after,~/.vim/bundle/vim-fugitive/after,~/.vim/bundle/command-t/after,~/.vim/bundle/plugin/after,~/.vim/bundle/sparkup/vim//after
set shiftwidth=4
set switchbuf=usetab
set tabstop=4
" vim: set ft=vim :
