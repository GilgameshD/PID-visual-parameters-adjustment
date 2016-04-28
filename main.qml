import LineCharts 1.0
import QtQuick 2.0

// the whole window
Rectangle
{
    id: opacitytest;
    width: 720; height: 530
    color: "#edf0f0"

    property int monthNow: 0
    property int monthCount: 0
    property int nameWidth: 0
    property int today:0
    property int todayLocation:0

    Component.onCompleted:
    {
        nameWidth = 1000;   // define the width of the x axis
    }

    // the block showing the chart
    Rectangle
    {
        id: name
        anchors.top:pageHeader.bottom
        x:todayLocation                                 // set the origin position
        color: "#009955"
        width: nameWidth; height: 530

        LineChart
        {
            id: lineChart
            anchors.centerIn: parent
            width: nameWidth; height: 530
            color: "white"
            onChartCleared: console.log("The chart has been cleared")
        }
    }
    Text
    {
        anchors.top:name.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text:qsTr("PID parameters setting")
        color: "#ffffff"
        font.pointSize: 20;
    }

    MouseArea
    {
        anchors.fill: parent
        drag.target: name
        drag.axis: "XAxis"
        drag.minimumX: -(nameWidth-720)
        drag.maximumX: 0
        onClicked:
        {
            lineChart.clearChart()
        }
    }
}
