const basicController = {};
basicController.get= (req,res) => {
    res.json({
        message: 'Welcome to Projection.'
    })
};
export default basicController;