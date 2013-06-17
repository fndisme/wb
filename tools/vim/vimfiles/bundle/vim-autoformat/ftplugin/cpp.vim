"Set the formatter name and arguments for this filetype
let s:prgname   = "astyle"
let s:arguments = "--mode=c --style=java -s2 --brackets=attach --pad-oper --add-brackets --keep-one-line-statements --align-pointer=type -m0 -M60 -Y"

"Set the formatprg option, if the formatter is installed
"globally or in the formatters/ folder
call g:FindFormatter(s:prgname, s:arguments)
