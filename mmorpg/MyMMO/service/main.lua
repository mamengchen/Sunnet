local skynet = require "skynet"
local socket = require "skynet.socket"
local pb = require "protobuf"

local players = {}

local function broadcast_position()
    local msg = { players = {} }
    for id, pos in pairs(players) do
        table.insert(msg.players, { player_id = id, x = pos.x, y = pos.y, z = pos.z })
    end
    local data = pb.encode("ServerBroadcast", msg)

    for id, player in pairs(players) do
        socket.write(player.fd, data)
    end
end

local function handle_client(fd)
    socket.start(fd)
    while true do
        local data = socket.read(fd)
        if not data then
            break
        end

        local msg = pb.decode("PlayerMove", data)
        if msg then
            players[msg.player_id] = { fd = fd, x = msg.x, y = msg.y, z = msg.z }
            broadcast_position()
        end
    end
    socket.close(fd)
end

skynet.start(function()
    local addr = "0.0.0.0"
    local port = 8888
    local listen_fd = socket.listen(addr, port)
    print("Server started on " .. addr .. ":" .. port)
    pb.register_file("./proto/message.pb")
    socket.start(listen_fd, function(fd, addr)
        print("Client connected from:", addr)
        skynet.fork(handle_client, fd)
    end)
end)

-- 测试接入的protobuf
-- local skynet = require "skynet"
-- local pb = require "protobuf"

-- function test4()
--     pb.register_file("./proto/login.pb")
--     local msg = {
--         id = 101,
--         pw = "123456",
--     }
--     local buff = pb.encode("login.Login", msg)
--     print("len:"..string.len(buff))

--     local umsg = pb.decode("login.Login", buff)
--     if umsg then
--         print("id:"..umsg.id)
--         print("pw:"..umsg.pw)
--     else
--         print("error")
--     end
-- end



-- skynet.start(function()
--     test4()
-- end)