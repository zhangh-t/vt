function notifyReady() {
	qtReadyNotifier.ready();
}

function notifyActualSizeChanged() {
	 var background = $("#container").find(".highcharts-background");
    if (background != null) {
    	 var width = background.attr("width");
    	 var height = background.attr("height");
    	 qtReadyNotifier.actualSizeChanged(width, height);
    }
}