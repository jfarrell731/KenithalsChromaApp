KenithalsChromaApp = {
	Character = {
		Class = nil;
	}
}

local function onEnter(...)
	if KenithalsChromaApp["Character"].Class == nil or KenithalsChromaApp["Character"].Class ~= UnitClass("player") then
		KenithalsChromaApp["Character"].Class = UnitClass("player");
	end
end

local function onHealthChange(...)
	local totalHP = UnitHealthMax("player")
	local currentHP = UnitHealth("player")
	local percentHP = (currentHP / totalHP) * 100

	print("Health:" .. math.floor(percentHP))
end


local Frame = CreateFrame("Frame")
Frame:RegisterEvent("ADDON_LOADED")

Frame:SetScript("OnEvent", function(self, event, ...)
		local arg1 = ...
		if(event == "ADDON_LOADED" and arg1 == "KenithalsChromaApp_WoWAddon") then onEnter() end
	end)