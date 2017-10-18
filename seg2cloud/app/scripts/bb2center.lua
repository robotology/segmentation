-- loading lua-yarp binding library
require("yarp")

--
-- accept is called when the port receives new data
-- @param thing The Things abstract data type
-- @return Boolean
-- if false is returned, the data will be ignored 
-- and update() will never be called
PortMonitor.accept = function(thing)
    return true
end

--
-- update is called when the port receives new data
-- @param thing The Things abstract data type
-- @return Things
PortMonitor.update = function(thing)
    bt = thing:asBottle()
    if bt:size() == 2 then
        if bt:get(0):isInt() then
            return thing;
        end
    end
    bbox = bt:get(0):asList()
    th = yarp.Things()
    vec = yarp.Vector()

    if (bbox:size() == 4) then
        x = (bbox:get(0):asInt() + bbox:get(2):asInt())/2
        y = (bbox:get(1):asInt() + bbox:get(3):asInt())/2
    else
        x = -1
        y = -1
    end
    vec:push_back(x)
    vec:push_back(y)

    th:setPortWriter(vec)
    return th
end

