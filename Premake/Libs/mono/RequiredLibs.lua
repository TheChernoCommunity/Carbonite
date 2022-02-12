if common.host == "windows" then
	return {
		static = {
			"monosgen-2.0",
			"mono-component-debugger-static",
			"mono-component-diagnostics_tracing-static",
			"mono-component-hot_reload-static",
			"mono-profiler-aot",
			"coreclr.import"
		},
		shared = {
			"coreclr"
		}
	}
else
	return {
		static = {
			"monosgen-2.0",
			"mono-component-debugger-static",
			"mono-component-diagnostics_tracing-static",
			"mono-component-hot_reload-static",
			"mono-profiler-aot"
		},
		shared = {
			"coreclr"
		}
	}
end