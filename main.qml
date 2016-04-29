import LineCharts 1.0
import Communication 1.0
import QtQuick 2.0

// the whole window
Rectangle
{
    id: opacitytest;
    width: 1000; height: 530
    color: "#edf0f0"

    // define the width of the green background
    property int nameWidth: 700
    property bool opened : true

    Communication {id : communication}

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
                text : communication.dataToBeShown
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
                    opened = communication.openPort();
                     if(opened)
                         console.log("===========  port opened successfully  ============;")
                     else
                         console.log("===========  port opened failed  ===========")
                 }
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
                 anchors.fill: parent
                 onClicked:
                 {
                     communication.stop();
                     console.log("============  Port closed  ============")
                 }
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
                 anchors.fill: parent
                 onClicked:
                 {
                     // TODO
                     console.log("============  updating... ...  ===========")
                 }
             }
         }
        /******************************************************************************/
    }
}
