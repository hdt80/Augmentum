function onUpdate(diff)
end

function onShoot(target)
end

function onDamageDealt(dmg, hit)
	s = Stats:new(true);
	s:setStat("fireRate", -0.25);

	hit:applyStat(s);
end
