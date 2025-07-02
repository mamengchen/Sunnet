
-- local clsChat = {}
-- function clsChat:doOverChat()
--     local curTime = TIME.time()
--     local overCnt = DATA_CONST.getChatOverCnt()
--     local overTime = DATA_CONST.getChatOverTime()
    
--     -- 时间过期清理
--     while self._messages.head and (curTime - self._messages.head.timestamp) >= overTime do
--         self:_removeHead()
--     end
    
--     -- 数量超限清理
--     while self._messages.count > overCnt do
--         self:_removeHead()
--     end
-- end

-- function clsChat:_removeHead()
--     if self._messages.head then
--         local cid = self._messages.head.cid
--         self._messages.map[cid] = nil
--         self._messages.head = self._messages.head.next
--         if self._messages.head then
--             self._messages.head.prev = nil
--         else
--             self._messages.tail = nil
--         end
--         self._messages.count = self._messages.count - 1
--     end
-- end

-- function clsChat:addMessage(cid, data)
--     print(self._messages);
--     local newNode = {
--         cid = cid,
--         data = data,
--         timestamp = 2,
--         prev = self._messages.tail,
--         next = nil
--     }
    
--     if self._messages.tail then
--         self._messages.tail.next = newNode
--     else
--         self._messages.head = newNode
--     end
--     self._messages.tail = newNode
--     self._messages.map[cid] = newNode
--     self._messages.count = self._messages.count + 1
-- end

-- function clsChat:init()
--     print("ssssssssssssss");
--     self._messages = {
--         head = nil,  -- 最旧消息
--         tail = nil,   -- 最新消息
--         map = {},     -- cid => node
--         count = 0
--     }
--     for i = 1, 100 do
--         data = {id = i};
--         self:addMessage(i, data);
--     end
-- end

-- function clsChat:getMMM()
--     local tb1 = {}
--     local node = self._messages.head
--     while node do
--         table.insert(tb1, node.data)
--         node = node.next
--     end
--     for i = 1, #tb1 do
--         print(tb1[i].id)
--     end
--     return tb1
-- end
-- clsChat:init()
-- print(clsChat:getMMM());


local clschat = {1,23,"ssss",45,6,67,7,78,8,9}

for ky, val in pairs(clschat) do
    print(ky, val);
end

print("====================================================");
table.remove(clschat, 5);
for ky, val in pairs(clschat) do
    print(ky, val);
end

