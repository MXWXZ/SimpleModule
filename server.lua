local socket = require("socket")
local server = assert(socket.bind("*", 8888))
local ip, port = server:getsockname()

print("Server start at port 8888...")
while 1 do
    local client = server:accept()
    print("Connect in.")

    local line, err = client:receive()
    if not err then
        print(line)
    end

    client:close()
    print("Connect closed.")
    break -- only receive once
end
