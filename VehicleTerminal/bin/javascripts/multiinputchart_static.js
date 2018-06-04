Highcharts.setOptions({
    global: {
        useUTC: false
    }
});


function highChartDescription () {
    this.sTitle = "N/A";
    this.sSubTitle = "";
    this.sYAxisTitle = "N/A";
    this.seriesArray = [];
    this.xAxisCategories = [];
    this.legend = null;
    this.valueSuffix = "";
    this.createOption = function () {
        var option = {};
        option.title = {text : this.sTitle, x : -20};
        if (this.sSubTitle != null && this.sSubTitle != ""){
            option.subtitle = {text : this.sSubTitle, x : -20};
        }
        option.xAxis = {categories:this.xAxisCategories};
        option.yAxis = {title:this.sYAxisTitle};
        if (this.valueSuffix != null && this.valueSuffix != ""){ 
            option.tooltip = {valueSuffix : this.valueSuffix};
        }
        if (this.legend != null) {
            option.legend = this.legend;
        }
        var serieses = [];
        this.seriesArray.forEach(function (item) {
            var singleSeries = {name : item.name,
                                color : item.color,
                                data : item.data};
            serieses.push(singleSeries);
        });
        option.series = serieses;
        option.exporting = {enabled:false};
        return option;
    }
}


var chartDescription = new highChartDescription();
var highChartInstance = null;

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
    

function call_from_qt_init_chart(chartOptionString) {
    var chartOptionJSON = JSON.parse(chartOptionString);
    chartDescription.sTitle = chartOptionJSON.title;
    chartDescription.sSubTitle = chartOptionJSON.subTitle;
    chartDescription.sYAxisTitle = chartOptionJSON.yAxisTitle;
    chartDescription.seriesArray = chartOptionJSON.seriesSchemaArray; 
    chartDescription.xAxisCategories = chartOptionJSON.categories;
    chartOptionJSON.legend = chartOptionJSON.legend;
    chartOptionJSON.valueSuffix = chartOptionJSON.valueSuffix;
    highChartInstance = new Highcharts.Chart('container', chartDescription.createOption());  
    notifyActualSizeChanged();
}
    
$(document).ready(function () {
    notifyReady();
})

