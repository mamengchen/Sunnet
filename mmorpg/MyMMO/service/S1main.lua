local skynet = require "skynet"
local socket = require "skynet.socket"

local function handle_client(fd)
    socket.start(fd)
    while true do
        local msg = socket.read(fd)
        if msg then
            print("Received:", msg)
        else
            socket.close(fd)
            break
        end
    end
end

skynet.start(function()
    local addr = "0.0.0.0"
    local port = 8888
    local listen_fd = socket.listen(addr, port)
    print("Listening on " .. addr .. ":" .. port)

    socket.start(listen_fd, function(fd, addr)
        print("Client connected from:", addr)
        skynet.fork(handle_client, fd)
    end)
end)
