import app from './app';
//pulls from app.js, now we have access from app anywhere we want to
//not just one file.
app.listen(3000,() => {
    console.log("Running on port 3000");
});