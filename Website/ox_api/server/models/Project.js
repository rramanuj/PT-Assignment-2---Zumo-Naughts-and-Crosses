import mongoose from 'mongoose';
//defines everything that goes inside a collection
const { Schema } = mongoose;
mongoose.Promise = global.Promise;


//first instance of our schema, this is for the user accounts.
const projectSchema = new Schema({
   title: {type: String, required: true},
   _team: [ {type: Schema.ObjectId, ref: 'User'}],
   link: String,
   text: String,
   isDeleted: {type: Boolean, default: false},
   createdAt: {type: Date, default: Date.now},  //
   _creator: {type: Schema.ObjectId, ref: 'User'}, //references to the user
   //array to hold all the comments pertaining to a specific post
});


const autoPopulateCreator = function(next) {
    this.populate ({
        path: '_team',
        select: 'username id'
    });
next(); 
};


//This Pre function serves 2 purposes: 
// 1. As with the other models, it pre populates the user ID with the user name
// 2. It automatically sets the first person in the team member to be the person who created the team.
projectSchema.pre('find', autoPopulateCreator).pre('save', function (next) {
    this._team = this.get('_creator'); // considering _id is input by client
    next();
});

const Project = mongoose.model('Project', projectSchema);
export default Project;


