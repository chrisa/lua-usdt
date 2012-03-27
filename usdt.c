#define LUA_LIB
#include <lua.h>
#include <lauxlib.h>
#include <usdt.h>

#include <stdio.h>

typedef struct usdt_provider_obj {
        usdt_provider_t *provider;
} usdt_provider_obj_t;

typedef struct usdt_probedef_obj {
        usdt_probedef_t *probedef;
} usdt_probedef_obj_t;

static int
provider(lua_State *L)
{
        const char *name = luaL_checklstring(L, 1, NULL);
        const char *module = luaL_checklstring(L, 2, NULL);
        usdt_provider_obj_t *object = lua_newuserdata(L, sizeof(usdt_provider_obj_t));

        object->provider = usdt_create_provider(name, module);

        luaL_getmetatable(L, "usdt_provider_t");
        lua_setmetatable(L, -2);
        return 1;
}

static int
provider_probe(lua_State *L)
{
        usdt_provider_obj_t *self = luaL_checkudata(L, 1, "usdt_provider_t");
        const char *name = luaL_checklstring(L, 2, NULL);
        const char *func = luaL_checklstring(L, 3, NULL);

        usdt_probedef_obj_t *object = lua_newuserdata(L, sizeof(usdt_probedef_t *));
        object->probedef = usdt_create_probe(name, func, 0, NULL);
        usdt_provider_add_probe(self->provider, object->probedef);

        luaL_getmetatable(L, "usdt_probedef_t");
        lua_setmetatable(L, -2);
        return 1;
}

static int
provider_enable(lua_State *L)
{
        usdt_provider_obj_t *self = luaL_checkudata(L, 1, "usdt_provider_t");
        usdt_provider_enable(self->provider);
        return 0;
}

static int
probedef_fire(lua_State *L)
{
        usdt_probedef_obj_t *self = luaL_checkudata(L, 1, "usdt_probedef_t");
        usdt_fire_probe(self->probedef->probe, 0, NULL);
        return 0;
}

static int
probedef_enabled(lua_State *L)
{
        usdt_probedef_obj_t *self = luaL_checkudata(L, 1, "usdt_probedef_t");
        int is = usdt_is_enabled(self->probedef->probe);
        lua_pushinteger(L, is);
        return 1;
}

static const luaL_reg usdt_functions[] = {
        {"provider", provider},
        {NULL, NULL}
};

static const luaL_reg usdt_provider_methods[] = {
        {"probe", provider_probe},
        {"enable", provider_enable},
        {NULL, NULL}
};

static const luaL_reg usdt_probedef_methods[] = {
        {"fire", probedef_fire},
        {"enabled", probedef_enabled},
        {NULL, NULL}
};

int
luaopen_usdt(lua_State *L){
        luaL_newmetatable(L, "usdt_provider_t");
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        luaL_register(L, NULL, usdt_provider_methods);

        luaL_newmetatable(L, "usdt_probedef_t");
        lua_pushvalue(L, -1);
        lua_setfield(L, -2, "__index");
        luaL_register(L, NULL, usdt_probedef_methods);

        luaL_register(L, "usdt", usdt_functions);

        return 1;
}
