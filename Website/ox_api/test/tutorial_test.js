var assert = require('assert');
var should = require('chai').should(); //should is a function.

describe('Basic Mocha Test', function(){
    it('should deal with objects', function(){
        var obj = {name: 'Rasesh', gender:'male'};
        var objb = {name: 'Rasesh', gender:'male'};

      //  obj.should.have.property('name').equal('Tim');
        obj.should.deep.equal(objb)
        //deep flag ignores the variable name for the test. (i.e deep in the content of the object.)
    })
});

describe('Basic Mocha Test 2', function(){
    it('should deal with objects', function(){
        var obj = {name: 'Rasesh', gender:'male'};
        var objb = {name: 'Rasesh', gender:'male'};

      //  obj.should.have.property('name').equal('Tim');
        obj.should.deep.equal(objb)
        //deep flag ignores the variable name for the test. (i.e deep in the content of the object.)
    });
    it('should allow testing nulls', function(){
        var iAmNull = null;
        should.not.exist(iAmNull)
   
    })
});

