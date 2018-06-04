
function call_from_qt_upate_data(value) {
    var point = highChartInstance.series[0].point[0];
    point.updateNewValue(value);
}


function call_from_qt_init_chart(optionString) {
    var options = JSON.parse(optionString);
    options.legend = {enabled:false};
    options.exporting = {enabled:false};
    $('#container').highcharts(options, function (chart) {
    	highChartInstance = chart;
    })
    notifyActualSizeChanged();
}
    
var highChartInstance = null;
$(document).ready(function () {
	notifyReady();
})


