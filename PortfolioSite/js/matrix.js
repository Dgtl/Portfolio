//var content = $('.hidden').text().split('');
//var tmpBinArray = binArray(content.length); //generate and store binary array
//var tmpArray = [];
//var index = 1;
//var OFFSET = 2;
var drawCount = 0;

$(function () {

    $('span.code').each(function () {
        draw($(this));
    });

});

function draw(element) {

    console.log('draw called');
    drawCount += 1;
    console.log('draw count is: ', drawCount);

    var content = element.text().split('');
    var tmpBinArray = binArray(content.length); //generate and store binary array
    var index = 1;
    var OFFSET = 2;


    var animation = setInterval(function () {
        decrypt(content, tmpBinArray, index, element);
        index += 1;
        if (index > content.length + OFFSET){
            clearInterval(animation);
            drawCount -= 1;
            console.log('draw count is: ', drawCount);
            console.log('draw complete');
        }
    }, generateSpeed(content.length));

}

//provides decryption effect on some array
function decrypt(charArray, binArray, index, element) {

    //real-time decryption effect
    var tmpArray = charArray.slice(0,index).concat(binArray.slice(index));
    fillText(tmpArray.join(''), element);

}

//fill element text area
function fillText(content, element ) {

    element.text(content);

}

//generate interval speed
function generateSpeed(content){

    var speed;

    if (content < 70) {
        speed = 100 + (Math.random() * 40);
        return speed;
    } else {
        speed = 1 + (Math.random() * 20);
        return speed;
    }
}

// return an array filled with random 1s and 0s
function binArray(length) {

    var array = [];

    for (var i = 0; i <= (length / 2); i++) {

        if (Math.random() > 0.5) {
            array.push(0);
            array.push(' ');
        } else {
            array.push(1);
            array.push(' ');
        }
    }

    return array;
}

//redo primary function on button click
function recrypt() {

    var button = $( "button")
    var WAIT_TIME = 2000;

    if (drawCount == 0) {

        $('span.code').each(function () {
            draw($(this));
        });

    } else {
        button.text( "Wait" );
        setTimeout( function(){
            button.text( "Decrypt" );
        }, WAIT_TIME);
    }
}
