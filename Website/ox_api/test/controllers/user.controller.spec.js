
var assert = require('assert'); //Chai for better assertions. This looks bad
var expect = require('chai').expect;
var should = require('chai').should(); //should is a function.
var chai = require('chai');
var chaiAsPromised = require('chai-as-promised')
var sinon = require('sinon');
chai.use(chaiAsPromised)
chai.should();
var userController = require('/server/controllers/userController.js');

//Runs for every test!!
describe('AuthController', function(){
    beforeEach(function settingUpRoles () {
        console.log('running before each!');
     //   authController.setRoles(['user'])
        });
/*beforeEach('this function is erroring intentionally', function errorFunction () {
   throw ({error: 'error'})
    });*/
//helps autonomous tests/
//.ONLY says only run THIS test!!
//.SKIP, better than commenting your code out. 
    describe('IsAuthorized', function(){
        var user = {};
        beforeEach(function() {
            user = {
                roles: ['user'],
                isAuthorized: function(neededRole) {
                    return this.roles.indexOf(neededRole) >= 0;
                }
            }
            sinon.spy(user,'isAuthorized');
            userController.setUser(user);
        });
        it ('Should return false if not authorized', function(){
           // assert.equal(false, authController.isAuthorized('admin'))
           var isAuth = userController.isAuthorized('admin');
           console.log(user.isAuthorized)
           user.isAuthorized.calledOnce.should.be.true;
           expect(isAuth).to.be.false; //so much cleaner!
        })

        it ('Should return true if authorized', function(){
            userController.setRoles(['user', 'admin']);
           // assert.equal(true, authController.isAuthorized('admin'))
        var isAuth = userController.isAuthorized('admin');
        isAuth.should.be.true;
        })
        //i'm thinking about this now, for later. TDD. Mocha lets you drop a phrase without the function.
        it('should not allow a get if not authorized');
        it('should allow get if authorized');
    })
    describe('IsAuthorizedAsync', function(){
        it ('Should return false if not authorized', function(done){
        userController.isAuthorizedAsync('admin', 
        function(IsAuth){
            assert.equal(false, IsAuth)
            done();
        });
    });
    describe('isAuthorizedPromise', function(){
        it ('Should return false if not authorized', function(){
        return userController.isAuthorizedPromise('admin').should.eventually.be.false;
        });
    });
});
    describe.only('getIndex', function(){
        var user = {};
        beforeEach(function() {
            user = {
                roles: ['user'],
                isAuthorized: function(neededRole) {
                    return this.roles.indexOf(neededRole) >= 0;
                }
            }
        });
        it('should render index if authorized', function(){
            //stubs renders the isAuthorized function redundant, we dont need it
            //the data is stubbed!
            var isAuth = sinon.stub(user, 'isAuthorized').returns(true);
            var req = {user: user};
            var res = {
                render: function(){}
            };

            var mock = sinon.mock(res); //we mock the entire object here.
            mock.expects('render').once().withExactArgs('index'); //called with index in the res

            userController.getIndex(req,res); // i need to pass tbhings into get Index.
            isAuth.calledOnce.should.be.true;
          /*  res.render.calledOnce.should.be.true; //combining sinon & chai.
            res.render.firstCall.args[0].should.equal('index');*/

            mock.verify();
        })
    })
 });