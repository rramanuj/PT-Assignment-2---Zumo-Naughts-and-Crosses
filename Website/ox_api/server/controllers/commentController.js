import db from './../models';
import cardController from './cardController';

const commentController = {};


commentController.editComment = (req,res) => {  
    const {text, isDeleted, _id} = req.body;
    console.log(req.body);
    //pulls from our request body.

    //update
    db.Comment.findByIdAndUpdate(_id,
        { $set: {text, isDeleted} }
        ).then((newComment) => {
        res.status(200).json({
            success: true,
            data: true,
            data: newComment,
        });
    }).catch((err)=>{       //throws err if not 
        res.status(500).json ({
            message: err,
        });
    });
},
commentController.deleteComment = (req,res) => {  
    const {_id, isDeleted} = req.body;
    console.log(req.body);
    //pulls from our request body.

    //update
    db.Comment.findByIdAndUpdate(_id,
        { $set: {isDeleted} }
        ).then((newComment) => {
        res.status(200).json({
            success: true,
            data: true,
            data: newComment,
        });
    }).catch((err)=>{       //throws err if not 
        res.status(500).json ({
            message: err,
        });
    });
}


commentController.post = (req,res) => {
    const {text, userId, cardId} = req.body;
    console.log(req.body);
    //pulls from our request body.

    //Validation
    //user cursor, we can create a new instance of this model
    const comment = new db.Comment({
        text,
        _creator: userId,
        _card: cardId
    });
    //tries to save it.
    comment.save().then((newComment)=>{
    db.Card.findByIdAndUpdate(cardId,
        { $push: {'_comments': newComment._id} }
        ).then((exisitingPost) => {
        res.status(200).json({
            success: true,
            data: true,
            data: newComment,
            exisitingPost,
        });
    }).catch((err)=>{       //throws err if it's a javaScript error & database errors.
        res.status(500).json ({
            message: err.toString()
        });
    });
}).catch((err) => {
    res.status(500).json({
        message:err.toString(),
    });
});
}
export default commentController;

