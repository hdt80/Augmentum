config = {
	string = "aa",
	int = 3,
	float = 4.5,
	bool = false,

	EnemyType = {
		id = 1,
		name = "LUA_LOADED",
		sides = 5,
		default_stats = {
			range = 500,
			fireRate = 2,
			damage = 2,
			speed = 15,
			projSpeed = 50,
			accel = 0.9
		},
		level_diff_stats = {
			range = 15,
			fireRate = 0.1,
			damage = 0.1,
			speed = 0.2,
			projSpeed = 1,
			accel = 0.005
		}
	}
}
