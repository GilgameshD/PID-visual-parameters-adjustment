import LineCharts 1.0
import QtQuick 2.0

// the whole window
Rectangle
{
    id: opacitytest;
    width: 1000; height: 530
    color: "#edf0f0"

    property int monthNow: 0
    property int monthCount: 0
    property int nameWidth: 0
    property int today:0
    property int todayLocation:0

    Component.onCompleted:
    {
        nameWidth = 700;   // define the width of the green background
    }

    // the block showing the chart
    Rectangle
    {
        id: name
        anchors.top:pageHeader.bottom
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

    // the title at  the top of the chart
    Text
    {
        anchors.top:name.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        text:qsTr("PID parameters setting")
        color: "#ffffff"
        font.pointSize: 20;
    }

    // the data area in the right of the chart
    Rectangle
    {
        id: dataAera
        x:nameWidth
        color : "#6666CC"
        width : 1000 - nameWidth
        height : 530

        Text
        {
            anchors.top:dataAera.top
            anchors.topMargin: 15
            anchors.horizontalCenter: dataAera.horizontalCenter
            text:qsTr("Data windows")
            color: "#ffffff"
            font.pointSize: 15;
        }
        // update the data from the serial

        // buttons
        /****************************************************************************/
        Rectangle
        {
             id: openPort
             color: "grey"
             width: 80; height: 50

             // the position is based on its direct parent
             x : 10; y : 460;
             Text
             {
                 anchors.centerIn: openPort
                 color: "#ffffff"
                 text: qsTr("Open Port")
                 font.pointSize: 10
             }
             MouseArea
             {
                 onClicked: {lineChart.clearChart()}
             }
         }
        Rectangle
        {
             id: closePort
             color: "grey"
             width: 80; height: 50

             // the position is based on its direct parent
             x : 110; y : 460;
             Text
             {
                 anchors.centerIn : closePort
                 color : "#ffffff"
                 text : qsTr("Close Port")
                 font.pointSize : 10
             }
             MouseArea
             {
                 onClicked: {lineChart.clearChart()}
             }
         }
        Rectangle
        {
             id: updateData
             color: "grey"
             width: 80; height: 50

             // the position is based on its direct parent
             x : 210; y : 460;
             Text
             {
                 anchors.centerIn: updateData
                 color: "#ffffff"
                 text: qsTr("Update")
                 font.pointSize: 10
             }
             MouseArea
             {
                 onClicked: {lineChart.clearChart()}
             }
         }
        /******************************************************************************/
    }
}
