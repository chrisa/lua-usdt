package = "usdt"
version = "0.1-1"
source = {
   url = "file:///Users/chris/Projects/lua-usdt"
}
description = {
   summary = "C extension for DTrace USDT providers",
   detailed = [[
    Foo
   ]],
   homepage = "http://chrisa.github.com",
   license = "MIT/X11"
}
dependencies = {
   "lua >= 5.1"
}
supported_platforms = {
   "macosx",
   "unix",
   "!linux"
}
external_dependencies = {
   USDT = {
      header = "usdt.h" 
   }
}
build = {
    type = "builtin",
    modules = {
        usdt = {
            sources = "usdt.c",
            libraries = "usdt",
            incdirs = {"libusdt"},
            libdirs = {"libusdt"}
        }
    }
}
