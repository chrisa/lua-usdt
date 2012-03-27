lua-usdt
========

Lua bindings for libusdt[1].

Build with:

```
  luarocks build usdt-0.1-1.rockspec USDT_INCDIR=../libusdt USDT_LIBDIR=../libusdt
```

with a built libusdt alongside.

Test:

```
  sudo dtrace -Z \
     -n 'lua*:lmod:foo:cprobe{ printf("%s %s %s %s %s %s", copyinstr(arg0), copyinstr(arg1), \
         copyinstr(arg2), copyinstr(arg3), copyinstr(arg4), copyinstr(arg5)) }' \
     -n 'lua*:lmod:foo:iprobe{ printf("%d %d %d %d %d %d", arg0, arg1, arg2, arg3, arg4, \
         arg5) }' \
     -c 'lua test.lua'
```

[1] - https://github.com/chrisa/libusdt
