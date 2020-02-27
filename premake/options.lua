
-- Add switch to target iOS instead of macOS
if _TARGET_OS == 'macosx' then
	newoption {
		trigger     = 'ios',
		description = 'Target iOS'
	}
end
