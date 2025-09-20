import React, { useState } from 'react';
import './HelpBar.css';

export default function HelpBar() {
    const [isExpanded, setExpanded] = useState(false);

    const handleToggle = () => {
        setExpanded(!isExpanded);
    };

    return (
        <footer className={`HelpBar ${isExpanded ? 'Expanded' : ''}`}>
            <div className="Header" onClick={handleToggle}>
                <h4>ΒΟΗΘΕΙΑ</h4>
            </div>
            {isExpanded && (
                <div className="Content">
                    <div className="Questions-Answers">
                        <h4>Ερώτηση 1</h4>
                        <p>Απάντηση 1</p>
                    </div>
                    <div className="Questions-Answers">
                        <h4>Ερώτηση 2</h4>
                        <p>Απάντηση 2</p>
                    </div>
                    <div className="Questions-Answers">
                        <h4>Ερώτηση 3</h4>
                        <p>Απάντηση 3</p>
                    </div>
                    <div className="Questions-Answers">
                        <h4>Ερώτηση 4</h4>
                        <p>Απάντηση 4</p>
                    </div>
                    <div className="Questions-Answers">
                        <h4>Ερώτηση 5</h4>
                        <p>Απάντηση 5</p>
                    </div>
                    <div className="Questions-Answers">
                        <h4>Ερώτηση 6</h4>
                        <p>Απάντηση 6</p>
                    </div>
                </div>
            )}
        </footer>
    );
}
