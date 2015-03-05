//var content = $('.hidden').text().split('');
//var tmpBinArray = binArray(content.length); //generate and store binary array
//var tmpArray = [];
//var index = 1;
//var OFFSET = 2;
var count = 0;

$(function () {

    $('span.code').each(function() {
        draw($(this));
    });

});

//depreciated
function multiDraw(element) {

    count += 1;
    console.log("multiDraw called ", count, " times" );
    console.log(get_type(element));

    if (count > 50){
        return;
    }

    draw(element);

}

function draw(element) {

    console.log('draw called');
    console.log(get_type(element));

    var content = element.text().split('');
    var tmpBinArray = binArray(content.length); //generate and store binary array
    var index = 1;
    var OFFSET = 2;

    var animation = setInterval(function () {
        decrypt(content, tmpBinArray, index, element);
        index += 1;
        if (index > content.length + OFFSET){
            clearInterval(animation);
            console.log('draw complete');
        }
    }, generateSpeed(content.length));

}

//provides decryption effect on some array
function decrypt(charArray, binArray, index, element) {

    console.log('decrypt called');

    //hopefully real-time decryption effect
    var tmpArray = charArray.slice(0,index).concat(binArray.slice(index));
    //console.log(tmpArray.join(''));
    fillText(tmpArray.join(''), element);
    console.log(charArray.length);

    console.log('decrypt finished');

}

//fill main text area using jQuery
function fillText(content, element ) {

    element.text(content);

}

//generate interval speed
function generateSpeed(content){
    if (content < 70) {
        return 100 + (Math.random() * 40);
    } else {
        return 1+ (Math.random() * 20);
    }
}

// return an empty array filled with random 1s and 0s
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

//temp function to determine object's type
function get_type(thing) {
    if (thing === null) return "[object Null]"; // special case
    return Object.prototype.toString.call(thing);
}
