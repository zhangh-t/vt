Highcharts.setOptions({
    global: {
        useUTC: false
    }
});

function highChartSeries () {
    this.name = "N/A";
    this.color= "#000000";
    this.overflowThreshold = 0;
    this.pointCount = 0;
}


function highChartDescription () {
    this.nSeriesCount = 0;
    this.sTitle = "N/A";
    this.sYAxisTitle = "N/A";
    this.tickPixelInterval = 30;
    this.seriesSchemaArray = []
    this.seriesArray = [];
    this.enableXAxisLabels = true;
    this.legend = {enabed:false}
    this.createSeries = function () {
        var size = this.seriesSchemaArray.length;
        for (var i = 0 ; i < size ; ++i) {
            var schema = this.seriesSchemaArray[i];
            var series = new highChartSeries;
            series.name = schema.name;
            series.color = schema.color;
            series.overflowThreshold = schema.overflowThreshold;
            chartDescription.seriesArray[i] = (series);
        }     
    }
    
    this.getSeries = function () {
            var res = new Array(chartDescription.nSeriesCount);
            for (var i = 0 ; i < chartDescription.nSeriesCount; ++i) {
                var seriesJson = {}
                var seriesSchema = chartDescription.seriesArray[i];
                seriesJson.lineWidth = 1;
                seriesJson.name = seriesSchema.name;
                seriesJson.color = seriesSchema.color;
                seriesJson.data = [[(new Date()).getTime(), 0]];
                res[i] = seriesJson;
            }
            return res;
    }
    
    this.createOption = function () {
        var option = {};
        option.chart = {
            type: 'spline',
            animation: false, // don't animate in old IE
            marginRight: 10,
            events: {
                load: function () {
                    highChartInstance = this;
                }
            }};
        option.title = {text: chartDescription.sTitle};
        option.xAxis = {
        									type: 'datetime',
                        	tickPixelInterval: chartDescription.tickPixelInterval,
                        	labels : {
                        		enabled: this.enableXAxisLabels}
                       };
        option.yAxis = {
                        title: {
                                text: chartDescription.sXAxisTitle
                        },
                        plotLines: [{
                                value: 0,
                                width: 1,
                                color: '#808080'
                        }]   
                        }
        option.tooltip = {
                            formatter: function () {
                                                return '<b>' + this.series.name + '</b><br/>' +
                                                Highcharts.dateFormat('%Y-%m-%d %H:%M:%S', this.x) + '<br/>' +
                                                Highcharts.numberFormat(this.y, 2);
                                }
                         }
        option.legend = {enabled:false};
        option.series = this.getSeries();
        option.exporting = {enabled:false};
        option.plotOptions = {
                series:{
                    marker:{
                        enabled:false
                    }
                }
            };
        return option;
      }
      
}

var chartDescription = new highChartDescription();
var highChartInstance = null;

function call_from_qt_upate_data(seriesIndex, value) {

    if (seriesIndex < chartDescription.nSeriesCount) {
        var series = highChartInstance.series[seriesIndex];
        var threshold = chartDescription.seriesArray[seriesIndex].overflowThreshold;
        var shift = threshold > 0 && chartDescription.seriesArray[seriesIndex].pointCount
                       > threshold;
        series.addPoint([(new Date()).getTime(), value], true, shift) 
        if (!shift && threshold > 0) {
            chartDescription.seriesArray[seriesIndex].pointCount++;
        }
    }
}

function call_from_qt_init_chart(optionString) {
    var options = JSON.parse(optionString);
    chartDescription.nSeriesCount = options.seriesCount;
    chartDescription.sTitle = options.title;
    chartDescription.sYAxisTitle = options.yAxisTitle;
    chartDescription.tickPixelInterval = options.tickPixelInterval;
    chartDescription.seriesSchemaArray = options.seriesSchemaArray;
    chartDescription.legend = options.legend;
    chartDescription.enableXAxisLabels = options.xAxis.labels.enabled;
    chartDescription.createSeries();
    $('#container').highcharts(chartDescription.createOption());
    notifyActualSizeChanged();
}

function clearSeries(series) {
    if (series) {
        var emptyArray = new Array;
        series.setData(emptyArray, true, false, false);
    }  
}

function call_from_qt_clear_series(seriesIndex) {
    var seriesArray = highChartInstance.series;
    var size = seriesArray.length;
    if (seriesIndex >= 0 && seriesIndex < size) {
        var series = highChartInstance.series[seriesIndex];
        clearSeries(series);  
    }
}

function call_from_qt_clear_all () {
    var seriesArray = highChartInstance.series;
    seriesArray.forEach(function (singleSeries) {
        clearSeries(singleSeries)        
    });
}
        
$(document).ready(function () {
	notifyReady();
})

