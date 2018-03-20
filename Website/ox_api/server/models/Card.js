import mongoose from 'mongoose';
//Used the following video to help set the back end API using mongoose:
//https://www.youtube.com/watch?v=L5Nle1VXYnw
//defines everything that goes inside a collection
const { Schema } = mongoose;
mongoose.Promise = global.Promise;
//at some point I will do this

//first instance of our schema, this is for the cards..
const cardSchema = new Schema({
   title: {type: String, required: true},
   description: {type: String, required: true},
   board: {type: String, required: true}, //board
   deadline: {type: Date, required: true},
   createdAt: {type: Date, default: Date.now}, 
   isDeleted: {type: Boolean, default: false},
//    _owner: {type: Schema.ObjectId, ref: 'User'}, //references to the the action user, the person the card is assigned to..
    _owner: {type: String, required: false}, //references to the the action user, the person the card is assigned to..
   _creator: {type: Schema.ObjectId, ref: 'User'}, //references to the user
   _project: {type: Schema.ObjectId, ref: 'Project'},  //references the project.
   _comments: [ {type: Schema.ObjectId, ref: 'Comment'} ] 
});

const autoPopulateCreator = function(next) {
    this.populate ({
        path: '_creator',
        select: 'username -_id'
    }).populate ({
        path: '_project',
        select: 'title'
    }).populate({
        path: '_comments',
        select: 'text userId createdAt',  //you can chain these functions*/;
        match: {'isDeleted': false}})
next(); 
};

//autopopulates when this is mentioned, this works similiar to a 'didSet' in Swift. This ties the 
//meta data such as the creator username, and time to a comment automatically when the comment
//is generated. 
cardSchema.pre('find', autoPopulateCreator)
//searches for the user within the comment, and automatically populates the username and created at 
const Card = mongoose.model('Card', cardSchema);
export default Card;


