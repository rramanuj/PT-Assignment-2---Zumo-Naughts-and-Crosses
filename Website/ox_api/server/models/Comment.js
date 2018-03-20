import mongoose from 'mongoose';
//defines everything that goes inside a collection
const { Schema } = mongoose;
mongoose.Promise = global.Promise;
//at some point I will do this

//first instance of our schema, this is for the user accounts.
const commentSchema = new Schema({
   text: {type: String, required: true},
   isDeleted: {type: Boolean, default: false},
   createdAt: {type: Date, default: Date.now},
   _creator: {type: Schema.ObjectId, ref: 'User'}, //references to the user
   _card: {type: Schema.ObjectId, ref: 'Card'}  //references the post.
});



//we use this so we don't have to constantly call this function each time !!
const autoPopulateCreator = function(next) {
    this.populate ({
        path: '_creator',
        select: 'username'
    });
next(); 
};

//autopopulates when this is mentioned, this works similiar to a 'didSet' in Swift. This ties the 
//meta data such as the creator username, and time to a comment automatically when the comment
//is generated.
commentSchema.pre('find', autoPopulateCreator)
//searches for the user within the comment, and automatically populates the username and created at 
const Comment = mongoose.model('Comment', commentSchema);
export default Comment;


