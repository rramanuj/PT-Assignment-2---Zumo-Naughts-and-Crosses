var chai = require('chai');
var should = chai.should();
var sinon = require('sinon');
var request = require('supertest');
var app = require('config/express');

describe('post', function() {
    request(app)
        .get('/api/books')
        .expect('Content-Type', /json/)
        .expect('Content-Length', '4')
        .expect(200, "ok")
        .end(function(err, res) {
           if (err) throw err;
        });
});

/*projectController.post= (req,res) => {
    const {
        title,
        text,
        link,
        team,
        userId //token
    } = req.body;
//validation is required, either text or link not both. 
    const project = new db.Project({
        //es 25 shorthand, we don;t need to add the property namne with it
        title,
        text,
        link,
        _team:team,
        _creator: userId,       //since the property name is difeferent we need to specificy the 
                                ///parameter name.
    });
    project.save().then((newProject)=>{
        return res.status(200).json({
            success:true,
            data: newProject
        });
    }).catch((err) => {
        return res.status(500).json({
            message: err
        });
    })
};*/