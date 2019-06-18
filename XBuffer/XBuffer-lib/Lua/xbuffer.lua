xbuffer = {}

-- 获取版本号
function xbuffer.getversion()
    return "1"; -- 1.0协议版本
end

-- 反序列化数据
function xbuffer.load(bytes)

end

-- 反序列化数据
function xbuffer.tobytes(data)

end

------------------------------------
-- 消息对名的扩展元表

xbuffer.message = {}
local message = xbuffer.message;

function message:getversion()
    
end


return xbuffer