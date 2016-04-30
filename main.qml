import LineCharts 1.0
import QtQuick 2.0

// the whole window
Rectangle
{
    id: opacitytest;
    width: 1000; height: 530
    color: "#edf0f0"

    // be able to move the window
    MouseArea
    {
        id: dragRegion
        anchors.fill: parent
        property point clickPos: "0,0"
        onPressed:
        {
            clickPos = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged:
        {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            mainwindow.setX(mainwindow.x+delta.x)
            mainwindow.setY(mainwindow.y+delta.y)
        }
    }

    // define the width of the green background
    property int nameWidth: 700
    property bool opened : false

    // the block showing the chart
    Rectangle
    {
        id: name
        anchors.top:parent.top
        color: "#009955"
        width: nameWidth; height: 530

        LineChart
        {
            id: lineChart
            anchors.centerIn: parent
            width : nameWidth; height: 530
            color : "white"
            onChartCleared: console.log("The chart has been cleared")
        }
    }

    // the title at  the top of the chart
    Text
    {
        anchors.top : name.top
        anchors.topMargin : 20
        anchors.horizontalCenter : parent.horizontalCenter
        text:qsTr("PID parameters setting")
        color : "#ffffff"
        font.pointSize : 20;
    }

    // the data area in the right of the chart
    Rectangle
    {
        id: dataAera
        x:nameWidth
        color : "#6666CC"
        width : 1000 - nameWidth
        height : 530

        // the close button
        // TODO
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
        // we use many lines to update the data one by one
        // at begining, there are not so much data, so we disable some text line
        /****************************************************************************/
        Column
        {
            anchors.topMargin: 50
            anchors.top:parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Text
            {
                //text : qsTr(communication.returnData())
                font.weight: Font.Light
                font.pointSize : 10
            }
            Text
            {
                text: "hello world hello world"
                font.weight: Font.Normal
                font.pointSize : 12
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.DemiBold
                font.pointSize : 13
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Bold
                font.pointSize : 13
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Black
                font.pointSize : 13
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Black
                font.pointSize : 13
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Black
                font.pointSize : 13
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Black
                font.pointSize : 13
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Normal
                font.pointSize : 12
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Light
                font.pointSize : 10
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Light
                font.pointSize : 10
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Light
                font.pointSize : 10
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Light
                font.pointSize : 10
            }
            Text
            {
                text:"hello world hello world"
                font.weight: Font.Light
                font.pointSize : 10
            }
        }

        /****************************************************************************/

        // buttons, includes openport, closeport and updatedata
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
                 anchors.fill: parent
                 onClicked:
                 {
                    opened = lineChart.openComPort();
                    if(opened)
                        console.log("==============================  port opened successfully  ===========================")
                    else
                        console.log("==============================  port opened failed  ===========================")
                 }
             }
         }
        Rectangle
        {
             id: pause
             color: "grey"
             width: 80; height: 50

             // the position is based on its direct parent
             x : 110; y : 460;
             Text
             {
                 anchors.centerIn : pause
                 color : "#ffffff"
                 text : qsTr("Pause")
                 font.pointSize : 10
             }
             MouseArea
             {
                 anchors.fill: parent
                 onClicked:
                 {
                     lineChart.pausePort();
                     console.log("================================  Port paused  ==============================")
                 }
             }
         }
        Rectangle
        {
             id: restart
             color: "grey"
             width: 80; height: 50

             // the position is based on its direct parent
             x : 210; y : 460;
             Text
             {
                 anchors.centerIn: restart
                 color: "#ffffff"
                 text: qsTr("Restart")
                 font.pointSize: 10
             }
             MouseArea
             {
                 anchors.fill: parent
                 onClicked:
                 {
                     lineChart.restartPort();
                     console.log("==============================  restart  ==============================")
                 }
             }
         }
        /******************************************************************************/
    }
}
