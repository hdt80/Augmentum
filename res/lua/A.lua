function onUpdate(diff)
end

function onShoot(target)
end

function onDamageDealt(dmg, hit)
	local objs = getEnemiesInRange(hit:getX(), hit:getY(), 50);
	for k, v in pairs(objs) do
		v:applyDamage(1.0, attached);
	end
end
