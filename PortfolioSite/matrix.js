//var content = $('.hidden').text().split('');
//var tmpBinArray = binArray(content.length); //generate and store binary array
//var tmpArray = [];
//var index = 1;
//var OFFSET = 2;

$(function () {

    init($('#column1'));
    init($('#column2'));
    init($('#column3'));
});

function init(column) {

    console.log("init called");
    var content = column.find(".hidden").text().split('');
    var tmpBinArray = binArray(content.length); //generate and store binary array
    var index = 1;
    var OFFSET = 2;

    console.log(content.join(''));
    draw(content, tmpBinArray, index, OFFSET, column);

}

function draw(content, binArray, index, OFFSET, column) {

    console.log('draw called');

    console.log(content.join(''));

    var animation = setInterval(function () {
        decrypt(content, binArray, index, column);
        index += 1;
        if (index > content.length + OFFSET){
            clearInterval(animation);
            console.log('draw complete');
        }
    }, Math.random() * 30);

}

//provides decryption effect on some array
function decrypt(charArray, binArray, index, column) {

    console.log('decrypt called');

    //hopefully realtime decryption effect
    var tmpArray = charArray.slice(0,index).concat(binArray.slice(index));
    //console.log(tmpArray.join(''));
    fillText(tmpArray.join(''), column);
    console.log(index);

    console.log('decrypt finished');

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

//fill main text area using jQuery
function fillText(content, column ) {

    column.children(".code").text(content);

}

//temp function to determine object's type
function get_type(thing) {
    if (thing === null) return "[object Null]"; // special case
    return Object.prototype.toString.call(thing);
}
