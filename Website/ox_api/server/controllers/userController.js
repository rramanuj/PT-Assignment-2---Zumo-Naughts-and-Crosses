import db from './../models';

import bcrypt from 'bcrypt';
import session from 'express-session';
const config = require('../src/config');
const jwt = require('jsonwebtoken');

const userController = {};

/*function jwtSignUser (user){
    const ONE_WEEK = 60 * 60 * 24 * 7 //how long a session lastsf for
    return jwt.sign(user, config.authentication.jwtSecret, {expiresIn: ONE_WEEK}); //
}*/

//ends a JSON web token to store sessions..
function jwtSignUser (user){
return jwt.sign({
    data: user
  }, 'secret', { expiresIn: 60 * 60 });
}

userController.post = (req,res) => {
    const {username, password} = req.body;
    //pulls from our request body.
    //user cursor, we can create a new instance of this model
    const user = new db.User({
        username,
        password
    });
    
    //tries to save it.
    user.save().then((newUser)=>{
        res.status(200).json({      //if it does it does this
            success:true,
            data: newUser,
        });
    }).catch((err)=>{       //throws err if not 
          res.status(400).send ({
           error: err,
        });
    });
},


userController.authenticate = function (req,res) {
    const {username, password} = req.body;
  db.User.findOne({ username: username, isDeleted: false})
    .exec(function (err, user) {
      if (err) {
        return  
            res.status(400).send({
                error: "Incorrect username/password."
        })
      } else if (!user) {
        res.status(400).send({
            error: "Incorrect username/password."
    })
      }
      bcrypt.compare(password, user.password, function (err, result) {
        if (result === true) {
            res.status(200).send({
                success:true,
                user: user,
                token: jwtSignUser(user)
            });
    } else if (!result) {
            res.status(500).send({
                error: "Incorrect username/password."
        })
        } else {
        res.status(404).send({
            error: "Problems with server."
        })
    }})
})}

//flag as delete
userController.delete = function(req,res) {
    const {_id} = req.body;
    db.User.findByIdAndUpdate(_id,
        { $set: {isDeleted:true} }
        ).then((user) => {
        res.status(200).json({
            success: true,
            data: true,
            data: user,
        });
    }).catch((err)=>{       //throws err if not 
        res.status(500).json ({
            message: err,
        });
    });
}
userController.getAll = (req,res)=>{
        const {query} = req.body;
        db.User.find({
        username: { $regex: query  } 
        }, {username:1})//populate function uses the reference
            //creator in order to populate further information such as the usernamer etc
            .then((User) => {
            return res.status(200).json({
                success:true,
                data:User
            });
        }).catch((err) => {
            return res.status(500).json({
                message: err
            });
        });
    };

export default userController;

