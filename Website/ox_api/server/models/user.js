import mongoose from 'mongoose';
import bcrypt from 'bcrypt';
//defines everything that goes inside a collection
const { Schema } = mongoose;
mongoose.Promise = global.Promise;

//hashing a password before saving it to the database
//used https://medium.com/of-all-things-tech-progress/starting-with-authentication-a-tutorial-with-node-js-and-mongodb-25d524ca0359
//as a guide for password hashing/sessions.

//first instance of our schema, this is for the user accounts.
const userSchema = new Schema({
    username: {
        type: String,
        required: true,
        minlength: [5, 'Username must be 5 characters or more.']
    },
    password: {
        type: String,
        required: true,
        minlength: [8, 'Password must be 8 characters or more']
    },
    createdAt: {type: Date, default: Date.now},
    isDeleted: {type: Boolean, default:false},
});

userSchema.pre('save', function (next) {
    var user = this;
    bcrypt.hash(user.password, 10, function (err, hash){
      if (err) {
        return next(err);
      }
      user.password = hash;
      next();
    })
  });

//puts work before you save data you can add methods

const User = mongoose.model('User', userSchema);
export default User;


