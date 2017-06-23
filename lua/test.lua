foo = 4
bar = "Hi"

tower = Tower.new(1, 1, 1, 1);


function onUpdate(diff)
	print("update " .. diff .. "ms")
	tower:ret3();
	print(getX());
end
