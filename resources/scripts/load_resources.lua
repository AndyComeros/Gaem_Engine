
function load_resources()

	--load textures
	resources:LoadTexture("grass","resources/textures/terrain/grass.png");
	resources:LoadTexture("rock","resources/textures/terrain/rock.png");
	resources:LoadTexture("dirt","resources/textures/terrain/dirt.png");
	resources:LoadTexture("heightMap","resources/textures/heightmap/heightmap512.png");
	resources:LoadTexture("detailMap","resources/textures/terrain/detail.png");
	resources:LoadTexture("black","resources/textures/terrain/black.png");
	resources:LoadTexture("grid","resources/textures/terrain/tile_Specular2.png");

	resources:LoadTexture("AE86Diff","resources/textures/AE86.png");
	resources:LoadTexture("AE86Emis","resources/textures/AE86Emissive.png");
	resources:LoadTexture("AE86Spec","resources/textures/AE86Specular.png");

	resources:LoadTexture("buildingDiff","resources/textures/Untitled2022/buildingDiffuse.png");
	resources:LoadTexture("buildingEmiss","resources/textures/Untitled2022/buildingEmissive.png");
	resources:LoadTexture("buildingSpec","resources/textures/Untitled2022/buildingSpecular.png");

	resources:LoadTexture("water","resources/textures/Water/water.png");
	resources:LoadTexture("flowMap","resources/textures/Water/flow-speed-noise.png");
	resources:LoadTexture("DerivHeightMap","resources/textures/Water/water-derivative-height.png");

	resources:LoadTexture("Rock 2","resources/textures/rock.jpg");
	resources:LoadTexture("Palmdiff","resources/textures/Palmdiff.png");
	resources:LoadTexture("PalmEmiss","resources/textures/Palmemiss.png");

	resources:LoadCubemap("skybox",
		"resources/textures/skybox/Synthwave3/Right.png",
		"resources/textures/skybox/Synthwave3/Left.png",
		"resources/textures/skybox/Synthwave3/Top.png",
		"resources/textures/skybox/Synthwave3/Bottom.png",
		"resources/textures/skybox/Synthwave3/Front.png",
		"resources/textures/skybox/Synthwave3/Back.png"
	);

	--load models
	resources:LoadModel("arcade", "resources/models/untitled2022/Arcade.obj","arcade","","");
	resources:LoadModel("building1", "resources/models/untitled2022/CyberBuilding1.obj","buildingDiff","buildingEmiss","buildingSpec");
	resources:LoadModel("building2", "resources/models/untitled2022/CyberBuilding2.obj","buildingDiff","buildingEmiss","buildingSpec");
	resources:LoadModel("building3", "resources/models/untitled2022/CyberBuilding3.obj","buildingDiff","buildingEmiss","buildingSpec");
	resources:LoadModel("building4", "resources/models/untitled2022/CyberBuilding4.obj","buildingDiff","buildingEmiss","buildingSpec");
	resources:LoadModel("building5", "resources/models/untitled2022/CyberBuilding5.obj","buildingDiff","buildingEmiss","buildingSpec");
	resources:LoadModel("building6", "resources/models/untitled2022/CyberBuilding6.obj","buildingDiff","buildingEmiss","buildingSpec");
	resources:LoadModel("AE86", "resources/models/Toyota Sprinter Trueno AE86.obj", "AE86Diff", "AE86Emis", "AE86Spec");
	resources:LoadModel("Rock1", "resources/models/Rocks and Trees/Rock1.obj", "Rock 2", "", "");
	resources:LoadModel("Rock2", "resources/models/Rocks and Trees/Rock2.obj", "Rock 2", "", "");
	resources:LoadModel("Rock3", "resources/models/Rocks and Trees/Rock3.obj", "Rock 2", "", "");
	resources:LoadModel("Rock4", "resources/models/Rocks and Trees/Rock4.obj", "Rock 2", "", "");
	resources:LoadModel("Palm", "resources/models/Rocks and Trees/Palm.obj", "Palm", "Palmdiff", "PalmEmiss");

	--setup animated models
	resources:LoadTexture("robot","resources/models/md2/robot.png");
	resources:LoadTexture("robot_emiss","resources/models/md2/robot_emiss.png");
	resources:LoadTexture("robot_spec","resources/models/md2/robot_spec.png");
	resources:LoadAnimatedModel("robot","resources/models/md2/robot2.md2","robot","robot_emiss","robot_spec");
	resources:LoadAnimatedModel("dancer","resources/models/md2/dancer3.md2","robot","robot_emiss","robot_spec");
	resources:GetModel("dancer"):SetAnimationSpeed(10);

	robotModel = resources:GetModel("robot");
	robotModel:SetAnimation("idle"	, 0		, 30	, 50);
	robotModel:SetAnimation("run"	, 31	, 53	, 50);
	robotModel:SetAnimation("attack", 54	, 88	, 50);
	robotModel:SetAnimation("shoot"	, 89	, 124	, 50);
	robotModel:SetAnimation("fall"	, 125	, 191	, 50);

	--audio
	--Sound:addMusic("resources/audio/Initial D - Deja Vu.mp3");
	Sound:addSound("click","resources/audio/menu/click.wav");
	Sound:addSound("pause","resources/audio/menu/pause.wav");
	Sound:addSound("drift","resources/audio/car/drift.wav");
	Sound:addSound("engine","resources/audio/car/engine.wav");
	Sound:addSound("grunt","resources/audio/zombie/grunt.wav");
	Sound:addSound("carhit","resources/audio/zombie/carhit.wav");
	Sound:addSound("hitcar","resources/audio/zombie/hitcar.wav");

end
