import mongoose from 'mongoose';
//defines everything that goes inside a collection
const { Schema } = mongoose;
mongoose.Promise = global.Promise;
//at some point I will do this

//first instance of our schema, this is for the user accounts.
const teamSchema = new Schema({
   name: {type: String, required: true},
   isDeleted: {type: Boolean, default: false},
   createdAt: {type: Date, default: Date.now},
   _creator: {type: Schema.ObjectId, ref: 'User'}, //references to the user
   _members: [ {type: Schema.ObjectId, ref: 'User'} ], //array of users
   _project: {type: Schema.ObjectId, ref: 'Project', required: true}  //references the project.
});
//each team has an association to a project. 

const autoPopulateCreator = function(next) {
    this.populate ({
        path: '_members',
        select: 'username -_id'
    });
next();
};

//autopopulates when this is mentioned, this works similiar to a 'didSet' in Swift. This ties the 
//meta data such as the creator username, and time to a comment automatically when the comment
//is generated 
teamSchema.pre('find', autoPopulateCreator)
//searches for the user within the comment, and automatically populates the username and created at 
const Team = mongoose.model('Team', teamSchema);
export default Team;


