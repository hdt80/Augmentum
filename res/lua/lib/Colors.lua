local Colors = {}

function Colors.Red()
	return {
		R = 255,
		G = 0,
		B = 0,
		A = 255
	}
end

function Colors.Green()
	return {
		R = 0,
		G = 255,
		B = 0,
		A = 255
	}
end

function Colors.Blue()
	return {
		R = 0,
		G = 0,
		B = 255,
		A = 255
	}
end

function Colors.Black()
	return {
		R = 0,
		G = 0,
		B = 0,
		A = 255
	}
end

function Colors.White()
	return {
		R = 255,
		G = 255,
		B = 255,
		A = 255
	}
end

function Colors.Yellow()
	return {
		R = 255,
		G = 255,
		B = 0,
		A = 255
	}
end

function Colors.Magenta()
	return {
		R = 255,
		G = 0,
		B = 255,
		A = 255
	}
end

function Colors.Cyan()
	return {
		R = 0,
		G = 255,
		B = 255,
		A = 255
	}
end

function Colors.Transparent()
	return {
		R = 0,
		G = 0,
		B = 0,
		A = 0
	}
end

return Colors
