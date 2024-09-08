#!/bin/sh
# This file is public domain; see the LICENSE file located in the scripts directory.

die() {
    code=$1
    shift
    printf '\33[1;31mfatal:\33[m %s\n' "`echo "$@" | tr '\n' ' '`"
    exit "$code"
}

if [ -z "${1+deez}" ] || [ -z "${2+deez}" ]; then
    die 1 insufficient args provided! '(need 2)'
fi

case "$1" in
    file|clipboard);;
    *)
        die 2 first positional arg must be either \"file\" or \"clipboard\"\!
    ;;
esac

case "$2" in
    all|select);;
    *)
        die 3 second positional arg must be either \"all\" or \"select\"\!
    ;;
esac

# build the command and then eval it? Sure! what could go wrong???
cmd=grim
if [ "$2" = select ]; then
    cmd="$cmd"' -g "`slurp`"'
fi

# BUG: This will break if $HOME contains single quotes
if [ "$1" = file ]; then
    filename=" '$HOME/Pictures/Screenshots/""`date +%Y-%m-%d' '%H%M%S`.png""'"
    cmd="$cmd""$filename"
else
    cmd="$cmd"' - | wl-copy'
fi

#err_text="`(eval "$cmd") 2>&1`"
eval "$cmd"
exit_code=$?

if [ "$exit_code" -gt 0 ]; then
    notify-send -u critical 'Screenshot failed!' "\"$cmd\" exited with code $exit_code"
    exit 0
fi

if [ "$1" = file ]; then
    notify-send 'Screenshot taken!' "saved to $filename"
else
    notify-send 'Screenshot taken!' 'saved to system clipboard'
fi

