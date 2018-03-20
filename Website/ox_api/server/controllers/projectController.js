import db from './../models';
var mongodb = require('mongodb');

import { callbackify } from 'util';
const projectController = {};

//this is going to be a post, because we're creating a post.
projectController.post= (req,res) => {
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
};


//pulls from our request body.

//flag as delete
projectController.dropProject = function(req,res) {
const {projectId} = req.body;
db.Project.findByIdAndUpdate(projectId,
    { $set: {isDeleted:true} }
    ).then((project) => {
    res.status(200).json({
        success: true,
        data: true,
        data: project,
    });
}).catch((err)=>{       //throws err if not 
    res.status(500).json ({
        message: err,
    });
});
}
// This works on Postman but not on live server?
// projectController.dropProject = function(req,res) {
//     const {projectId} = req.body;
//     db.Project.findByIdAndRemove({_id: new mongodb.ObjectID(projectId)}, (err, project) => {  
//     // As always, handle any potential errors:
//     if (err) return res.status(500).send(err);
//     // We'll create a simple object to send back with a message and the id of the document that was removed
//     // You can really do this however you want, though.
//     const response = {
//         message: "project successfully deleted",
//         id: project._id
//     };
//     return res.status(200).send(response);
// })};

// projectController.dropProject = function (req,res) {
//     const {projectId} = req.body;
//     db.Project.findByIdAndRemove(
//         {_id: projectId}
//      ).remove()
//     },


projectController.searchTitle = function (req,res) {
    const {userId, query} = req.body;
    db.Project.find({
        _team:userId,  title: { $regex: query } }
    ).then((projects) => {
        return res.status(200).send({
            data:projects
        });
    }).catch((err) => {
        return res.status(500).json({
            message: err
        });
    })
},


projectController.addMember = (req,res) => {  
    const {userId, projectId} = req.body;
    
    //pulls from our request body.

    //Validation
    //user cursor, we can create a new instance of this model
    
    //update
    db.Project.findByIdAndUpdate(projectId,
        { $push: {'_team': userId} }
        ).then((newMember) => {
        res.status(200).json({
            success: true,
            data: true,
            data: newMember,
        });
    }).catch((err)=>{       //throws err if not 
        res.status(500).json ({
            message: err,
        });
    });
}
projectController.removeMember = (req,res) => {
    const {userId, projectId} = req.body;
    db.Project.findByIdAndUpdate(projectId,
        { $pull: {'_team': userId} }
        ).then((newMember) => {
        res.status(200).json({
            success: true,
            data: true,
            data: newMember,
        });
    }).catch((err)=>{       //throws err if not 
        res.status(500).json ({
            message: err,
        });
    });
},
//getTeam
projectController.getTeam = function (req,res) {
    const {projectId} = req.body;
    db.Project.find({
        _id:projectId}, {_team:1}
    ).then((projects) => {
        return res.status(200).send({
            data:projects
        });
    }).catch((err) => {
        return res.status(500).json({
            message: err
        });
    })
},

projectController.getProjectsByUser = function (req,res) {
    const {userId} = req.body;
    db.Project.find({
        _team:userId, isDeleted: false
    }).populate({ //populate function uses the reference
        //creator in order to populate further information such as the usernamer etc
        path: '_creator',
        //the -_id removes the id field from the postman api pull 
        select: 'username createdAt'}).populate({  //you can chain these functions
        //populates must be a path & select combo. 
        path: '_comments', //we only need the text here as the middleware
        //we implemented automatically extracts the _user from the id 
        select: 'text',
        path: 'team', //we only need the text here as the middleware
        //we implemented within the respective controller file automatically extracts the _user from the id.
        select: 'name -_id',
        match: {'isDeleted': false}}).then((projects) => {

        return res.status(200).json({success:true, data:projects})
        
    }).catch((err) => {
        return res.status(500).json({
            message: err
        });
    })
},
projectController.getById = (req,res)=>{
    const {projectId} = req.body;
    db.Project.find({
        _id:projectId
    }).populate({ //populate function uses the reference
        //creator in order to populate further information such as the usernamer etc
        path: '_creator',
        //the -_id removes the id field from the postman api pull 
        select: 'username createdAt'}).populate({  //you can chain these functions
        //populates must be a path & select combo. 
        path: '_comments', //we only need the text here as the middleware
        //we implemented automatically extracts the _user from the id 
        select: 'text',
      /*  path: '_team', //we only need the text here as the middleware
        //we implemented within the respective controller file automatically extracts the _user from the id.
        select: 'username _id',*/
        match: {'isDeleted': false}}).then((projects) => {
        return res.status(200).send({
            data:projects
        });
    }).catch((err) => {
        return res.status(500).json({
            message: err
        });
    })
},
//
projectController.getAll = (req,res)=>{
    db.Project.find({}).populate({ //populate function uses the reference
        //creator in order to populate further information such as the usernamer etc
        path: '_creator',
        //the -_id removes the id field from the postman api pull 
        select: 'username createdAt'}).populate({  //you can chain these functions
        //populates must be a path & select combo. 
        path: '_comments', //we only need the text here as the middleware
        //we implemented automatically extracts the _user from the id 
        select: 'text',
        path: 'team', //we only need the text here as the middleware
        //we implemented within the respective controller file automatically extracts the _user from the id.
        select: 'name -_id',
        match: {'isDeleted': false}}).then((projects) => {
        return res.status(200).json({
            success:true,
            data:projects
        });
    }).catch((err) => {
        return res.status(500).json({
            message: err
        });
    })
}

export default projectController;