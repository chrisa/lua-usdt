require("usdt")
print("loaded usdt")
print(usdt)
provider = usdt.provider("lua", "lmod")
print(provider)

probe = provider.probe(provider, "foo1", "bar1", "int")
print(probe)

provider.enable(provider)
print("enabled provider")

if (probe.enabled(probe)) then
  probe.fire(probe)
end
