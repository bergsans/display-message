# Display Message
In Vim it's possible, by visual selection, to evaluate parts* of a code written in an interpretted language. Out of the box,
the result from such a operation is outputted in the command window in NeoVim (in contrast to Vim outputting it as a background process at stdout). This is a nice feature, especially since you can mix-in any interpretive language on the fly.

![screen recording](assets/screenshot-1.png)

For exercise, I wanted to use C++, output the result of an evaluation in a floating window, centered and with large font.

I've only added support for JavaScript and have mapped the display-window to `<leader>i` in visual mode (presuming code is selected). The feature present in Vim is generic, meaning this is an extremly useless application although fair exercise.

```vimscript
function! GetResult()
    let result_cmd = system("node ~/Documents/dev/display-message/scratch-output")
    let output = "\n\n" . "==> " . result_cmd
    exec 'call system("echo \"" . expand(output) . "\" >> ~/Documents/dev/display-message/scratch-output")'
endfunction

vnoremap <leader>i :w! ~/Documents/dev/display-message/scratch-output<CR>:call GetResult()<CR>:!~/Documents/dev/display-message/build/fn-res<CR>
```

![screen recording](assets/screenshot-2.png)

This application is generic in the sense that it output the content of a scratch file to a floating window, meaning that it could be easily adapted for other purposes if you use a Window Manager such as X-Monad. I would recommend *(especially with X-Monad) Dzen.

# Dependencies
I use SDL2 and SDL_TTF, which must be installed if compiled using g++ and the repo make script.
