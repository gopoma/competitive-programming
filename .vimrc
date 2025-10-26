set cin aw ai is ts=4 sw=4 tm=50 nu noeb bg=dark ru cul
sy on | im jk <esc> | im kj <esc> | no ; :

ca Hash w !cpp -dD -P -fpreprocessed \| tr -d '[:space:]' \
\| md5sum \| cut -c-6

nnoremap <F5> :w<CR>:!g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -Wconversion -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL % -o ./bin/%:r<CR>

nnoremap <F6> :!./bin/%:r<CR>

nnoremap <S-F5> :w<CR>:!g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -Wconversion -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -DLOCAL % -o ./bin/%:r && ./bin/%:r<CR>
