-- local skynet = require "skynet"
-- local console = require "skynet.console"
-- local runconfig = require "runconfig"
-- skynet.start(function()
--     -- 初始化
--     skynet.error("[start main]")

--     -- 创建一个gateserver服务
--     skynet.newservice("gateway", "gateway", 1);

--     skynet.newservice("console") -- 添加控制台服务
--     -- 退出自身
--     skynet.exit()
-- end)


-- 解析json相关实例
package.cpath = package.cpath..";/home/mmc/mmorpg/OnePice/luaclib_src/lua-cjson/cjson.so"
local cjson = require("cjson")
print(cjson.encode({hello = "world"}))