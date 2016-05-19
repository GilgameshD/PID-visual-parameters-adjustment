import LineCharts 1.0
import QtQuick 2.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0

// the whole window
Item
{
    id: opacitytest;
    width: 1205; height: 535

    // draw shadow
    DropShadow
    {
            id: rectShadow1
            anchors.fill: source
            cached: true
            horizontalOffset: -3
            verticalOffset: -3
            radius: 7
            samples: 10
            color: "#80000000"
            smooth: true
            source: name
    }
    // draw shadow
    DropShadow
    {
            id: rectShadow2
            anchors.fill: source
            cached: true
            horizontalOffset: 3
            verticalOffset: 3
            radius: 7
            samples: 10
            color: "#80000000"
            smooth: true
            source: name
    }

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
    property int nameWidth: 1200
    property bool opened : false
    property bool fullScreen : false;

    // the block showing the chart
    Rectangle
    {
        id: background
        anchors.fill: parent
        //anchors.top:parent.top
        x : 3; y : 3
        color: "#009955"
        width: nameWidth; height: 530
        radius : 10
    }

    Rectangle
    {
        id: name
        x : 3+4; y : 3+70
        color: "#333333"
        width: nameWidth-8; height: 530-70-3
        radius : 10

        LineChart
        {
            id: lineChart
            anchors.centerIn: parent
            width : nameWidth; height: 530
            color : "white"
        }
    }

    // the title at  the top of the chart
    Text
    {
        anchors.top : background.top
        anchors.topMargin : 20
        anchors.horizontalCenter : parent.horizontalCenter
        text:qsTr("PID parameters setting")
        color : "#ffffff"
        font.pointSize : 20;
    }

    // buttons, includes openport, closeport and updatedata
    Rectangle
    {
         id: openPort
         color: "#333399"
         width: 80; height: 50; radius: width/2
         border.color: "white"

         // the position is based on its direct parent
         x : 900; y : 460;
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
             hoverEnabled: true
             onEntered: {parent.color = "#ff6666";}
             onExited:{parent.color = "#333399"}
             onClicked:
             {
                opened = lineChart.startPort();
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
         color: "#333399"
         width: 80; height: 50; radius: width/2
         border.color: "white"

         // the position is based on its direct parent
         x : 1000; y : 460;
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
             hoverEnabled: true
             onEntered: {parent.color = "#ff6666";}
             onExited:{parent.color = "#333399"}
             onClicked:
             {
                 lineChart.stopPort();
                 console.log("==================================  Port paused  ==============================")
             }
         }
    }
    Rectangle
    {
         id: restart
         color: "#333399"
         width: 80; height: 50;  radius: width/2
         border.color: "white"

         // the position is based on its direct parent
         x :1100; y : 460;
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
             hoverEnabled: true
             onEntered: {parent.color = "#ff6666";}
             onExited:{parent.color = "#333399"}
             onClicked:
             {
                 lineChart.restartPort();
                 console.log("====================================  restart  ====================================")
             }
         }
     }
/*
    // we can choose which port number to open
    ComboBox
    {
        currentIndex: 2
        model: ListModel
        {
            id: cbItems
            ListElement { text: "COM3"; color: "Yellow" }
            ListElement { text: "COM8"; color: "Green" }
            ListElement { text: "COM4"; color: "Brown" }
        }
        width: 200
        x:900; y:420
        onCurrentIndexChanged: console.debug(cbItems.get(currentIndex).color)
    }
*/
    // minimized button
    Rectangle
    {
         x: 1050; y: 20;
         width : 40; height : 30
         color : "yellow"
         radius: width/2;
         MouseArea
         {
             anchors.fill : parent
             hoverEnabled : true
             onEntered : {parent.color = "#ff6666";}
             onExited : {parent.color = "yellow"}
             onClicked : {mainwindow.showMinimized()}
         }
     }
    // maxizized button
    Rectangle
    {
         x: 1100; y: 20;
         width : 40; height : 30;
         color : "#9932cc"
         radius: width/2;
         MouseArea
         {
             anchors.fill: parent
             hoverEnabled: true
             onEntered :  {parent.color = "#ff6666";}
             onExited : {parent.color = "#9932cc"}
             onClicked :
             {
                 if(!fullScreen)
                 {
                    mainwindow.showFullScreen();
                    fullScreen = true;
                 }
                 else
                 {
                     mainwindow.showNormal();
                     fullScreen = false;
                 }
             }
         }
     }
    // close button
    Rectangle
    {
         x: 1150; y: 20;
         width : 40; height : 30;
         color : "red"
         radius: width/2;
         MouseArea
         {
             anchors.fill: parent
             hoverEnabled: true
             onEntered :  {parent.color = "#ff6666";}
             onExited : {parent.color = "red"}
             onClicked:{mainwindow.close()}
         }
     }
}
