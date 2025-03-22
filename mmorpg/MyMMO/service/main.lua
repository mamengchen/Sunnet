local socket = require "skynet.socket"

local clients = {}    -- 存储客户端连接

local function handle_message(client_fd, msg)
    for fd in pairs(clients) do
        if fd ~= client_fd then
            socket.write(fd, msg)
        end
    end
end

local function handle_connect(client_fd)
    clients[client_fd] = true
    socket.start(client_fd)

    while true do
        local msg = socket.read(client_fd)
        if not msg then break end
        handle_message(client_fd, msg)
    end

    clients[client_fd] = nil
end

skynet.start(function()
    local listen_fd = socket.listen("0.0.0.0", 8888)
    socket.start(listen_fd, function(client_fd, addr)
        skynet.fork(handle_connect, client_fd)
    end)
end)