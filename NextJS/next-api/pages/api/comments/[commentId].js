import { comments } from "../../../data/comments";

export default function handler(req, res) {
    const { commentId } = req.query
    
    if (req.method === 'GET') {

        const comment = comments.find( comment => comment.id === parseInt(commentId))
        res.status(200).json(comment)

    } else if (req.method === 'DELETE') {

        // getting elements to delete and finding its index
        const deleteComment = comments.find( (comment) => comment.id === parseInt(commentId) )
        const index = comments.findIndex( comment => comment.id === parseInt(commentId) )

        // removing element from index
        comments.splice(index, 1)

        // responding deleteComment
        res.status(200).json(deleteComment)

    }
    
}